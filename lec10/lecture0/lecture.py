import sys
from cs50 import SQL



db = SQL("sqlite:///lecture.db")

# name placeholder with ':<var>'
rows = db.execute("SELECT * FROM Album WHERE Title = :t", t = sys.argv[1])

for row in rows:
    print(row["Title"])