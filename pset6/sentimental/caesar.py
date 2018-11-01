import string
import sys
from cs50 import get_string

letters = list(string.ascii_uppercase)
k = int(sys.argv[1])

word = get_string("plaintext: ")

print("ciphertext: ", end = "")

for char in word:
    c = (letters.index(char) + k) % 25
    print(letters[c], end = "")

print("\n")