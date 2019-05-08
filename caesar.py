from cs50 import get_string
from sys import argv, exit

if len(argv) != 2 or not argv[1].isdigit():
    exit("Usage: ./caesar key")

key = int(argv[1]) % 26
pt = get_string("plaintext:  ")
print("ciphertext: ", end="")

for i in pt:
    if i.islower():
        print(chr(ord('a') + (ord(i) - ord('a') + key) % 26), end="")
    elif i.isupper():
        print(chr(ord('A') + (ord(i) - ord('A') + key) % 26), end="")
    else:
        print(i, end="")
print()