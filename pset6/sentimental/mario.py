from cs50 import get_int

i = get_int("Height: ")

for n in range(2, i+2):
    print(" "*(i+1-n), end = "")
    print("#"*n)