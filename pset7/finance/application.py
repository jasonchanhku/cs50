import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    users = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
    user_id = session["user_id"])
    name = db.execute("SELECT username FROM users WHERE id = :user_id", user_id = session["user_id"])
    quotes = {}

    sums = []
    for stock in stocks:
        quotes[stock["symbol"]] = lookup(stock["symbol"])
        sums.append(quotes[stock["symbol"]]["price"] * stock["total_shares"])
    cash_remaining = users[0]["cash"]
    total = cash_remaining + sum(sums)
    username = name[0]["username"]
    return render_template("index.html", quotes=quotes, stocks=stocks, total=total, cash_remaining=cash_remaining, username = username)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        print("quote is: ", quote)
        print('quote price is: ', quote["price"])
        if not quote:
            return apology("Invalid Quote applied")

        try:
            shares = int((request.form.get("shares")))
            print("Value is: ", shares)
        except:
            return apology("Invalid shares were input")

        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])

        cash_remaining = rows[0]["cash"]
        price_per_share = quote["price"]
        total_price = price_per_share * shares

        if total_price > cash_remaining:
            return apology("Insufficient cash ! Please top up more !")

        db.execute("UPDATE users SET cash = cash - :price WHERE id = :user_id", price=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price_per_share) VALUES(:user_id, :symbol, :shares, :price_per_share)",
        user_id = session["user_id"],
        symbol = quote["symbol"],
        shares = shares,
        price_per_share = quote["price"])

        flash("Purchase Successful")


        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT symbol, shares, price_per_share, created_at FROM transactions WHERE user_id = :user_id ORDER BY created_at ASC", user_id=session["user_id"])

    return render_template("history.html", transactions=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("Stock quote not valid!")
        else:
            return render_template("quoted.html", name = quote["name"], price = quote["price"],  symbol=quote["symbol"])


    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        elif request.form.get("password") != request.form.get("password_again"):
            return apology("passwords do not match!", 403)

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username does not exists
        if len(rows) == 1:
            return apology("Username already exists", 403)
        else:
            result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
            username = request.form.get("username"), hash = generate_password_hash(request.form.get("password")))

            print("user id is: ", result)
            session["user_id"] = result
            return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = list(db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = :user_id", user_id = session["user_id"]))
    if request.method == "POST":

        if not stocks:
            return apology("Missing Symbol")

        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("No such symbol")

        shares = int(request.form.get("shares"))

        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # How much $$$ the user still has in her account
        cash_remaining = rows[0]["cash"]
        price_per_share = quote["price"]

        # Calculate the price of requested shares
        total_price = price_per_share * shares

        # Book keeping (TODO: should be wrapped with a transaction)
        db.execute("UPDATE users SET cash = cash + :price WHERE id = :user_id", price=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price_per_share) VALUES(:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol"),
                   shares=-shares,
                   price=price_per_share)

        flash("Sold!")

        return redirect("/")

    else:
        return render_template("sell.html", stocks_list = stocks)

@app.route("/change", methods=["GET", "POST"])
@login_required
def change():

    """Change Password"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        rows = db.execute("SELECT * FROM users WHERE id = :user_id",
                          user_id = session["user_id"])

        # Ensure old password is correct
        if not check_password_hash(rows[0]["hash"],request.form.get("old_password")):
            return apology("old password is incorrect!", 403)

        # Ensure password was submitted
        elif not request.form.get("new_password"):
            return apology("must provide new password", 403)

        elif not request.form.get("new_password_again"):
            return apology("must provide new password again", 403)

        elif request.form.get("new_password") != request.form.get("new_password_again"):
            return apology("new passwords do not match!", 403)

        db.execute("UPDATE users SET hash = :new_password WHERE id = :user_id", new_password=generate_password_hash(request.form.get("new_password")), user_id=session["user_id"])

        flash("Password Changed!")

        return redirect("/")

    else:
        return render_template("change.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
