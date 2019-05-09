from crypt import crypt
from sys import argv, exit
import itertools

if len(argv) != 2 or len(argv[1]) != 13:
    exit("Usage: ./crack hash")

salt = argv[1][:2]
letters = list(map(chr, list(range(65, 91)) + list(range(97, 123))))

for i in letters:
    key = i
    if crypt(key, salt) == argv[1]:
        exit(key)
    for j in letters:
        key = i + j
        if crypt(key, salt) == argv[1]:
            exit(key)
        for k in letters:
            key = i + j + k
            if crypt(key, salt) == argv[1]:
                exit(key)
            for l in letters:
                key = i + j + k + l
                if crypt(key, salt) == argv[1]:
                    exit(key)
exit("invalid hash word.")