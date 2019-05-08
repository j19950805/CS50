from cs50 import get_string
from sys import argv, exit

if len(argv) != 2 or not argv[1].isalpha():
    exit("Usage: ./caesar key")

key = []
for i in argv[1]:
    if i.isupper():
        key.append(ord(i) - 65)
    else:
        key.append(ord(i) - 97)

pt = get_string("plaintext:  ")
print("ciphertext: ", end="")

k = 0
for j in pt:
    if j.islower():
        print(chr(97 + (ord(j) - 97 + key[k % len(key)]) % 26), end="")
    elif j.isupper():
        print(chr(65 + (ord(j) - 65 + key[k % len(key)]) % 26), end="")
    else:
        k -= 1
        print(j, end="")
    k += 1
print()