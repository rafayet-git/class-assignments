import os

from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use file  system (instead of    signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/settings")
@login_required
def settings():
    return render_template("settings.html")


@app.route("/changeuser", methods=["POST"])
@login_required
def changeuser():
    user = request.form.get("username")
    pw = request.form.get("password")
    if not user:
        return apology("must provide username", 400)
    elif not pw:
        return apology("must provide password", 400)
    rows = db.execute("SELECT * FROM users WHERE username = ?", user)
    if len(rows) != 0:
        return apology("username already exists", 400)
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    if not check_password_hash(rows[0]["hash"], pw):
        return apology("invalid password", 400)
    db.execute("UPDATE users SET username = ? WHERE id = ?", user, session["user_id"])
    flash("Successfully changed username!")
    return redirect("/")


@app.route("/changepass", methods=["POST"])
@login_required
def changepass():
    pw = request.form.get("password")
    pw2 = request.form.get("newpw")
    pw3 = request.form.get("newpwconfirm")
    if not pw:
        return apology("must provide current password", 400)
    elif not pw2:
        return apology("must provide new password", 400)
    elif not pw3:
        return apology("must provide new password again", 400)
    elif pw2 != pw3:
        return apology("new passwords do not match", 400)
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    if not check_password_hash(rows[0]["hash"], pw):
        return apology("invalid current password", 400)
    hash = generate_password_hash(pw2, method="pbkdf2:sha256", salt_length=8)
    db.execute("UPDATE users SET hash = ? WHERE id = ?", hash, session["user_id"])
    flash("Successfully changed password!")
    return redirect("/")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stockedbuys = db.execute("SELECT order_id, symbol, amount FROM orders WHERE user_id = ? AND type = 'Buy'", session["user_id"])
    bal = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    # track total price of all stocks
    stockprice = 0
    total = 0
    # make a full dictionary for each stock and variables, so it will work in for loop
    for stock in stockedbuys:
        if stock["amount"] != 0:
            # check total amount of stocks for the symbol
            for stock2 in stockedbuys:
                if stock["symbol"] == stock2["symbol"] and stock["order_id"] != stock2["order_id"]:
                    stock["amount"] += stock2["amount"]
                    stock2["amount"] = 0
                    stockedbuys.remove(stock2)
            stockedsell = db.execute(
                "SELECT symbol, amount FROM orders WHERE user_id = ? AND type = 'Sell' AND symbol = ?", session["user_id"], stock["symbol"])
            # check sold stocks and remove from total
            for stock2 in stockedsell:
                stock["amount"] -= stock2["amount"]
            quotedb = lookup(stock["symbol"])
            stock["name"] = quotedb["name"]
            stock["price"] = quotedb["price"]
            fullprice = quotedb["price"] * stock["amount"]
            stock["fullprice"] = fullprice
            stockprice += fullprice
            total = bal + stockprice
    # remove dicts with no stock
    for stock in stockedbuys:
        if stock["amount"] == 0:
            stockedbuys.remove(stock)
    return render_template("index.html", stockdb=stockedbuys, bal=bal, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        quote = request.form.get("symbol")
        quotedb = lookup(quote)
        if not quotedb:
            return apology("invalid symbol", 400)
        # check if num of shares if valid and positive
        num = request.form.get("shares")
        if not num or not num.isdigit() or int(num) < 1:
            return apology("invalid shares", 400)
        # find cash and see if user can afford
        cost = quotedb["price"] * int(num)
        bal = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if cost > bal:
            return apology("not enough balance", 400)
        bal = bal-cost
        # update balance
        db.execute("UPDATE users SET cash = ? WHERE id = ?", bal, session["user_id"])
        # add info to new table
        time = datetime.now()
        db.execute("INSERT INTO orders (user_id, symbol, amount, price, time, type) VALUES (?, ?, ?, ?, ?, 'Buy')",
                   session["user_id"], quote.upper(), int(num), cost, time)
        flash("Successfully bought " + quote.upper() + " stock!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    orderdb = db.execute("SELECT * FROM orders WHERE user_id = ?", session["user_id"])
    return render_template("history.html", orderdb=orderdb)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash("Successfully logged in!")
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
        quote = request.form.get("symbol")
        # use lookup to find symbol stats
        quotedb = lookup(quote)
        if not quotedb:
            return apology("invalid symbol", 400)
        # load quoted html
        return render_template("quoted.html", name=quotedb["name"], symbol=quotedb["symbol"], price=quotedb["price"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if (request.method == "POST"):
        usr = request.form.get("username")
        pw = request.form.get("password")
        pw2 = request.form.get("confirmation")
        if not usr:
            return apology("must provide username", 400)
        elif not pw:
            return apology("must provide password", 400)
        # check if 2nd password was provided
        elif not pw2:
            return apology("must provide password again", 400)
        rows = db.execute("SELECT * FROM users WHERE username = ?", usr)
        if len(rows) != 0:
            return apology("username already exists", 400)
        # check if both pw's match
        elif pw != pw2:
            return apology("passwords do not match", 400)
        # make hash of password
        hash = generate_password_hash(pw, method="pbkdf2:sha256", salt_length=8)
        # add to database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", usr, hash)
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not shares or not shares.isdigit() or int(shares) < 1:
            return apology("invalid shares", 400)
        stockdb = db.execute("SELECT * FROM orders WHERE user_id = ? AND symbol = ? AND type = 'Buy'", session["user_id"], symbol)
        if len(stockdb) == 0:
            return apology("invalid symbol", 400)
        stocksold = db.execute("SELECT * FROM orders WHERE user_id = ? AND symbol = ? AND type = 'Sell'",
                               session["user_id"], symbol)
        # count total shares the person has
        stockcount = 0
        for stock in stockdb:
            stockcount += stock["amount"]
        for stock in stocksold:
            stockcount -= stock["amount"]
        if int(shares) > stockcount:
            return apology("not enough shares", 400)
        quotedb = lookup(symbol)
        price = quotedb["price"] * int(shares)
        # add sell value to db
        time = datetime.now()
        db.execute("INSERT INTO orders (user_id, symbol, amount, price, time, type) VALUES (?, ?, ?, ?, ?, 'Sell')",
                   session["user_id"], symbol.upper(), int(shares), price, time)
        # change money
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", price, session["user_id"])
        flash("Successfully sold " + symbol.upper() + " stock!")
        return redirect("/")
    else:
        # load current symbols
        stockdb = db.execute("SELECT DISTINCT symbol FROM orders WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", stockdb=stockdb)
