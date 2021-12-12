import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash, safe_str_cmp
from datetime import datetime

from helpers import apology, login_required, lookup, eur

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
app.jinja_env.filters["eur"] = eur

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///rebalance.db")

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Define variables that describe the users portfolio using SQL queries
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    stocks = db.execute(
        "SELECT stock AS symbol, SUM(CASE WHEN transaction_type='buy' THEN shares WHEN transaction_type='sell' THEN -shares ELSE NULL END) AS shares FROM transactions WHERE user_id = ? GROUP BY stock", session["user_id"])
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
        stock["price"] = quote_dict["price"]
        stock["total"] = stock["price"] * stock["shares"]
        net_worth += stock["total"]

    return render_template("index.html", cash=cash, stocks=stocks, net_worth=net_worth)


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


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":


        # Ensure username was submitted
        #if not request.form.get("username"):
        #    return apology("must provide username", 400)

        # Ensure password was submitted
        #elif not request.form.get("password"):
        #    return apology("must provide password", 400)

        # Ensure password and re-typed password match
        #elif not safe_str_cmp(request.form.get("password"), request.form.get("confirmation")):
        #    return apology("password confirmation does not match", 400)

        # Query database for username
        #rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username does not exist
        #if len(rows) != 0:
        #    return apology(f"username {request.form.get('username')} already exists", 400)

        # Register the user (i.e. add user and hash to the database)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Redirect user to login page with info message
        #flash("You were successfully registered")
        return render_template("home.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)