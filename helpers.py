from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    lines_a = set()
    lines_b = set()

    for line in a:
        lines_a.add(line.rstrip("\n"))

    for line in b:
        lines_b.add(line.rstrip("\n"))

    return list(lines_a & lines_b)


def sentences(a, b):
    """Return sentences in both a and b"""

    sentences_a = set([s.replace('\n', ' ') for s in sent_tokenize(a)])
    sentences_b = set([s.replace('\n', ' ') for s in sent_tokenize(b)])

    return list(sentences_a & sentences_b)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substrings_a = set()
    substrings_b = set()

    for word in a.split():
        if len(word) >= n:
            for i in range(len(word) - n):
                substrings_a.add(word[i:i + n])

    for word in b.split():
        if len(word) >= n:
            for i in range(len(word) - n):
                substrings_b.add(word[i:i + n])

    return list(substrings_a & substrings_b)
