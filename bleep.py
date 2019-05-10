from cs50 import get_string
from sys import argv


def main():
    words = set()
    if len(argv) != 2:
        exit(1)
    file = open(argv[1], "r")
    for line in file:
        words.add(line.rstrip("\n"))
    file.close()

    x = get_string("What message would you like to censor?\n")
    y = x.split()

    for i in y:
        if i.lower() in words:
            print("*"*len(i), end=" ")
        else:
            print(i, end=" ")
    print()


if __name__ == "__main__":
    main()
