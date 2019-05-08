from cs50 import get_int

# Ask credit card number from user
while True:
    x = get_int("Number:")
    if x > 0:
        break

y = x // pow(10, 12)
sum_digit = 0

# Calculate number by algorithm
while x >= 1:
    digit1 = x % 10
    digit2 = x // 10 % 10
    if digit2 * 2 // 10 == 0:
        sum_digit = sum_digit + digit2 * 2 + digit1
    else:
        sum_digit = sum_digit + digit2 * 2 % 10 + 1 + digit1
    x = x // 100

# Check if the number is valid
if sum_digit % 10 != 0:
    print("INVALID")
# Check if the number is AMEX
elif y // 10 == 34 or y // 10 == 37:
    print("AMEX")
# Check if the number is MASTERCARD
elif y // 100 <= 55 and y // 100 > 50:
    print("MASTERCARD")
# Check if the number is VISA
elif y // 1000 == 4 or y == 4:
    print("VISA")
else:
    print("INVALID")