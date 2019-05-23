import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT symbol,SUM(shares) share FROM history WHERE id= :id GROUP BY symbol", id=session["user_id"])
    sum_value = 0
    for stock in stocks:
        stock["currentprice"] = lookup(stock["symbol"])['price']
        stock["name"] = lookup(stock["symbol"])['name']
        stock["value"] = lookup(stock["symbol"])['price'] * stock['share']
        sum_value = sum_value + stock["value"]
        stock["value"] = usd(stock["value"])

    cash = db.execute("SELECT cash FROM users WHERE id= :id", id=session["user_id"])
    total = cash[0]["cash"] + sum_value

    return render_template("index.html", stocks=stocks, cash=usd(cash[0]["cash"]), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)
        quote = lookup(request.form.get("symbol"))
        # Ensure symbol was valid
        if not quote:
            return apology("invalid symbol", 400)

        # Ensure shares were submitted
        if not request.form.get("shares"):
            return apology("missing shares", 400)
        if not (request.form.get("shares")).isnumeric() or int(request.form.get("shares")) < 0:
            return apology("invalid shares", 400)

        cost = quote['price'] * int(request.form.get("shares"))
        cash = db.execute("SELECT cash FROM users WHERE id= :id", id=session["user_id"])
        if cost > cash[0]["cash"]:
            return apology("can't afford", 400)
        else:
            db.execute(
                "INSERT INTO history(id, symbol, price, shares) VALUES(:id, :symbol, :price, :shares)",
                id=session["user_id"],
                symbol=request.form.get("symbol"),
                price=quote['price'],
                shares=int(request.form.get("shares")))

            db.execute("UPDATE users SET cash=cash - :cost WHERE id= :id", id=session["user_id"], cost=cost)

            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    # Query database for username
    username = request.args.get("username")
    usernamecheck = db.execute("SELECT username FROM users WHERE username= :username", username=username)
    if len(username) > 0 and not usernamecheck:
        return jsonify(True)
    return jsonify(False)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM history WHERE id= :id", id=session["user_id"])
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        quote = lookup(request.form.get("symbol"))
        # Ensure symbol was valid
        if not quote:
            return apology("invalid symbol", 400)

        price = usd(quote['price'])

        return render_template("quoted.html", quote=quote, price=price)

        # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif (request.form.get("confirmation") != request.form.get("password")):
            return apology("passwords don't match", 400)

        username = request.form.get("username")
        usernamecheck = db.execute("SELECT username FROM users WHERE username= :username", username=username)
        if len(username) < 1 or usernamecheck:
            return apology("username taken", 400)

        db.execute(
            "INSERT INTO users(username, hash) VALUES(:username, :hash)",
            username=username,
            hash=generate_password_hash(request.form.get("password")))

        registered = db.execute("SELECT id FROM users WHERE username= :username",
                                username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = registered[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        # Ensure shares were submitted
        if not request.form.get("shares"):
            return apology("missing shares", 400)

        shares = int(request.form.get("shares"))
        yourshares = db.execute("SELECT SUM(shares) share FROM history WHERE id= :id AND symbol= :symbol",
                                id=session["user_id"], symbol=request.form.get("symbol"))
        if shares > yourshares[0]["share"]:
            return apology("too many shares", 400)

        quote = lookup(request.form.get("symbol"))

        earn = quote['price'] * shares
        db.execute(
            "INSERT INTO history(id, symbol, price, shares) VALUES(:id, :symbol, :price, :shares)",
            id=session["user_id"],
            symbol=request.form.get("symbol"),
            price=quote['price'],
            shares=-shares)

        db.execute("UPDATE users SET cash=cash + :earn WHERE id= :id", id=session["user_id"], earn=earn)
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        stocks = db.execute("SELECT symbol FROM history WHERE id= :id GROUP BY symbol", id=session["user_id"])
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
