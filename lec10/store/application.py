from flask import Flask, redirect, render_template, request, session
from flask_session import Session

# Configure app
app = Flask(__name__)

# Configure sessions
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Items for sale
ITEMS = ["foo", "bar", "baz"]

@app.route("/")
def index():
    return render_template("index.html")


@app.route("/update", methods=["POST"])
def update():
    # this prints ImmutableMultiDict([('foo', '5'), ('bar', '6'), ('baz', '7')])
    print(request.form)
    for item in request.form:
        # prints individual keys, foo, bar, baz
        print(item)
        # prints the value
        print(int(request.form.get(item)))
        # get(item) gets the value of item
        session[item] = int(request.form.get(item))
    return redirect("/cart")


@app.route("/cart")
def cart():
    return render_template("cart.html", cart=session)