from nltk.tokenize import sent_tokenize

def substring_tokenize(string, n):

    substring = []

    for i in range(len(string) - n +1 ):
        substring.append(string[i:i+n])

    return substring

def lines(a, b):
    """Return lines in both a and b"""
    # TODO
    a_lines = set(a.split("\n"))
    b_lines = set(b.split("\n"))

    return a_lines & b_lines


def sentences(a, b):
    """Return sentences in both a and b"""
    a_sen = set(sent_tokenize(a))
    b_sen = set(sent_tokenize(b))
    # TODO
    return a_sen & b_sen


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    a_sub = set(substring_tokenize(a, n))
    b_sub = set(substring_tokenize(b, n))
    # TODO
    return a_sub & b_sub
