import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash, safe_str_cmp
from datetime import datetime

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Define variables that describe the users portfolio using SQL queries
    cash =  db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    stocks =  db.execute("SELECT stock AS symbol, SUM(CASE WHEN transaction_type='buy' THEN shares WHEN transaction_type='sell' THEN -shares ELSE NULL END) AS shares FROM transactions WHERE user_id = ? GROUP BY stock", session["user_id"])
    net_worth = cash

    # Remove stocks with zero shares
    indexes = []
    for i in range(len(stocks)):
        if stocks[i]['shares'] == 0:
            indexes.append(i)

    for index in sorted(indexes, reverse=True):
        del stocks[index]

    # Add updated info on each of the user's holdings
    for stock in stocks:
        quote_dict = lookup(stock["symbol"])
        stock["name"] = quote_dict["name"]
        stock["price"] =  quote_dict["price"]
        stock["total"] = stock["price"] * stock["shares"]
        net_worth += stock["total"]

    return render_template("index.html", cash=cash, stocks=stocks, net_worth=net_worth)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Define variables for transaction
        shares = request.form.get("shares")
        price = lookup(request.form.get("symbol"))["price"]
        symbol = lookup(request.form.get("symbol"))["symbol"]
        cash =  db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        if not symbol:
            return apology("stock not found", 400)
        elif cash < price * int(shares):
            return apology(f'Insufficient funds: you are trying to buy {shares} shares of {symbol} at ${round(price)} for a total of ${round(int(shares) * price)} but you only have ${round(cash)}.', 400)
        else:
            # Register the transaction into the database
            db.execute("INSERT INTO transactions (user_id, year, month, day, hour, minute, transaction_type, stock, shares, price) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", session["user_id"], datetime.now().year, datetime.now().month, datetime.now().day, datetime.now().hour, datetime.now().minute, "buy", symbol, shares, price)

            # Update user's cash
            db.execute("UPDATE users SET cash=? WHERE id=?", cash - int(shares) * price, session["user_id"])

            # Redirect user to index page with info message
            flash("Transaction completed sucessfully")
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        quote_dict = lookup(request.form.get("symbol"))
        if not quote_dict:
            return apology("stock not found", 400)
        else:
            return render_template("quoted.html", quote_dict=quote_dict)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password and re-typed password match
        elif not safe_str_cmp(request.form.get("password"), request.form.get("confirmation")):
            return apology("password confirmation does not match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username does not exist
        if len(rows) != 0:
            return apology(f"username {request.form.get('username')} already exists", 400)

        # Register the user (i.e. add user and hash to the database)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Redirect user to login page with info message
        flash("You were successfully registered")
        return render_template("login.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Retrieve current symbols and shares of stocks owned by the user
    stocks =  db.execute("SELECT stock AS symbol, SUM(CASE WHEN transaction_type='buy' THEN shares WHEN transaction_type='sell' THEN -shares ELSE NULL END) AS shares FROM transactions WHERE user_id = ? GROUP BY stock", session["user_id"])

    # Remove stocks with zero shares
    indexes = []
    for i in range(len(stocks)):
        if stocks[i]['shares'] == 0:
            indexes.append(i)

    for index in sorted(indexes, reverse=True):
        del stocks[index]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Define variables for transaction
        shares = int(request.form.get("shares"))
        symbol = request.form.get("symbol")
        price = lookup(symbol)["price"]
        cash =  db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        if not symbol or symbol not in [stocks[i]['symbol'] for i in range(len(stocks))]:
            return apology("stock not found", 400)
        elif shares < 0:
            return apology("number of shares must be positive", 400)
        else:
            # Check that user owns enough shares of the requested stock
            for i in range(len(stocks)):
                if stocks[i]['symbol'] == symbol:
                    max_shares = stocks[i]['shares']
                    if shares > max_shares:
                        return apology("you do not own enough shares", 400)

            # Register the transaction into the database
            db.execute("INSERT INTO transactions (user_id, year, month, day, hour, minute, transaction_type, stock, shares, price) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", session["user_id"], datetime.now().year, datetime.now().month, datetime.now().day, datetime.now().hour, datetime.now().minute, "sell", symbol, shares, price)

            # Update user's cash
            db.execute("UPDATE users SET cash=? WHERE id=?", cash + shares * price, session["user_id"])

            # Redirect user to index page with info message
            flash("Transaction completed sucessfully")
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
