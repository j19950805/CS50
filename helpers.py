from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    return list(set(a.splitlines()) & set(b.splitlines()))


def sentences(a, b):
    """Return sentences in both a and b"""

    return list(set(sent_tokenize(a)) & set(sent_tokenize(b)))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substrings_a = set()
    substrings_b = set()

    for word in a.split():
        if len(word) >= n:
            for i in range(len(word) - n + 1):
                substrings_a.add(word[i:i + n])

    for word in b.split():
        if len(word) >= n:
            for i in range(len(word) - n + 1):
                substrings_b.add(word[i:i + n])

    return list(substrings_a & substrings_b)
