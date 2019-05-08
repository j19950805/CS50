from cs50 import get_float

while True:
    dollars = get_float("Change owed:")
    if dollars > 0:
        break

# Change dollars to cents
cents = round(dollars * 100)

# Calculate how many coins do customer get back and print the result
cash = cents // 25 + cents % 25 // 10 + cents % 25 % 10 // 5 + cents % 25 % 10 % 5
print(cash)