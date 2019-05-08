from cs50 import get_int

while True:
    x = get_int("Height:")
    if x <= 8 and x > 0:
        break

for i in range(x):
    print(" "*(x - i - 1), end="")
    print("#"*(i + 1), end="")
    print("  ", end="")
    print("#"*(i + 1), end="")
    print()