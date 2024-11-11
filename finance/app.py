import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    username = db.execute("SELECT username FROM users WHERE id=?", user_id)[0]["username"]

    shares = db.execute(
        "SELECT symbol, CAST(SUM(no_of_shares) AS INTEGER) AS total_shares FROM shares JOIN users ON shares.buyer_id=users.id WHERE users.id = ? GROUP BY symbol", user_id)

    # Takes the symbol from the db to pass to the lookup function to find the current price
    prices = {}
    costs = {}
    for share in shares:
        symbol = share["symbol"]
        result = lookup(symbol)

        if result:
            prices[symbol] = result["price"]

            costs[symbol] = round(prices[symbol] * share["total_shares"], 2)

    # Finds the sum of the costs
    total_cost = sum(costs.values())

    cash = db.execute("SELECT ROUND(cash,2) FROM users WHERE id = ?", user_id)[0]["ROUND(cash,2)"]

    total_value = round(total_cost + cash, 2)

    # Passes the details to index.html
    return render_template("index.html", username=username, shares=shares, prices=prices, costs=costs, total_cost=total_cost, cash=cash, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # Checks for an invalid input
        try:
            symbol = request.form.get("symbol")
        except ValueError:
            return apology("Please enter a valid symbol")
        # Checks for an empty symbol
        if not symbol:
            return apology("Please enter a symbol")

        result = lookup(symbol)

        # Checks if the result of the lookup is None
        if result is None:
            return apology("Invalid symbol")

        price_per_share = result["price"]

        shares = request.form.get("shares")

        # Checks if the input is an integer
        try:
            shares = int(shares)
        except ValueError:
            return apology("Please enter an integer")
        # Checks if the shares is less than or equal to zero
        if shares <= 0:
            return apology("Please enter positive shares")

        total_price_paid = shares * price_per_share

        user_id = session["user_id"]

        purchase_date = datetime.now()

        # current_balance is a list of dictionaries. By accessing [0]["cash"] you get the cash value from the first (and only) dictionary in the list
        current_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if current_balance < total_price_paid:
            return apology("You do not have the funds to complete this purchase")

        else:
            new_balance = current_balance - total_price_paid

        db.execute("INSERT INTO shares (symbol, no_of_shares, cost, buyer_id, date, price_per_share)VALUES(?,?,?,?,?,?)",
                   symbol, shares, total_price_paid, user_id, purchase_date, price_per_share)

        db.execute("INSERT INTO history (symbol, no_of_shares, cost, user_id, date, price_per_share, transaction_type)VALUES(?,?,?,?,?,?,'buy')",
                   symbol, shares, total_price_paid, user_id, purchase_date, price_per_share)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, user_id)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    rows = db.execute(
        "SELECT symbol, no_of_shares, date, price_per_share, transaction_type, cost FROM history WHERE user_id = ?", user_id)

    return render_template("history.html", rows=rows)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
        # Get the name of stock
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please enter a symbol")
        else:
            # Assign the lookup function to the result variable
            result = lookup(symbol)
            if result == None:
                return apology("Please enter a valid ticker symbol")
            name = result['name']
            price = result['price']
            print(name, price)
            # Get the page where the lookup values will be rendered
            return render_template("quoted.html", name=name, price=price)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Gets the username of the user
        username = request.form.get("username")
        # Ensures username is submitted
        if not username:
            return apology("Please enter a username")
        # Checks if username already exists in the database
        rows = db.execute("SELECT username FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("This username already exists")
        # Gets the password for the account and hashes it
        password = request.form.get("password")
        hashed_password = generate_password_hash(password)
        # Ensures if password is submitted
        if not password:
            return apology("Please enter a password")
        # User re-enters the password
        confirmation = request.form.get("confirmation")
        # Ensures confirmation password is submitted
        if not confirmation:
            return apology("Please re-enter the password")
        # Checks if the confirmation password and original match
        if confirmation != password:
            return apology("Passwords do not match")
        # Account data stored in the database
        db.execute("INSERT INTO users (username, hash)VALUES(?, ?)", username, hashed_password)
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please pick a symbol")

        user_id = session["user_id"]

        # Lookup stock price
        result = lookup(symbol)
        price_per_share = result["price"]

        # Get the number of shares available for this user and symbol
        available_shares = db.execute(
            "SELECT CAST(SUM(no_of_shares) AS INTEGER) AS total_shares FROM shares WHERE symbol = ? AND buyer_id = ? GROUP BY symbol", symbol, user_id)[0]["total_shares"]

        # Checks if input is an integer
        try:
            shares_to_sell = int(request.form.get("shares"))
        except ValueError:
            return apology("Please enter an integer")

        if shares_to_sell > available_shares:
            return apology("You do not have enough shares")

        total_price_received = shares_to_sell * price_per_share

        # current_balance is a list of dictionaries. By accessing [0]["cash"] you get the cash value from the first (and only) dictionary in the list
        current_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        new_balance = current_balance + total_price_received

        # Insert the sale into the history table
        sell_date = datetime.now()
        db.execute("INSERT INTO history (symbol, no_of_shares, cost, user_id, date, price_per_share, transaction_type)VALUES(?,?,?,?,?,?,'sell')",
                   symbol, shares_to_sell, total_price_received, user_id, sell_date, price_per_share)

        share_rows = db.execute(
            "SELECT id, no_of_shares FROM shares WHERE symbol = ? AND buyer_id = ? AND status = 'active' ORDER BY date ASC", symbol, user_id)

        remaining_shares_to_sell = shares_to_sell

        # Deduct shares from the oldest purchases first
        for row in share_rows:
            row_id = row["id"]
            row_shares = row["no_of_shares"]

            if remaining_shares_to_sell <= row_shares:
                # Subtracts all remaining shares from this row
                db.execute("UPDATE shares SET no_of_shares = no_of_shares - ? WHERE id = ?",
                           remaining_shares_to_sell, row_id)

                # If no shares remain in this row, mark it as 'sold'
                if remaining_shares_to_sell == row_shares:
                    db.execute("UPDATE shares SET status = 'sold' WHERE id = ?", row_id)
                break
            else:
                # Subtract all shares from this row and move to the next
                db.execute("UPDATE shares SET no_of_shares = 0 WHERE id = ?", row_id)
                remaining_shares_to_sell -= row_shares

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, user_id)

        return redirect("/")
    else:
        # Lists shares available for sale in the HTML
        user_id = session["user_id"]
        shares = db.execute(
            "SELECT DISTINCT symbol FROM shares WHERE buyer_id = ? AND status = 'active'", user_id)
        return render_template("sell.html", shares=shares)


@app.route("/password", methods=["GET", "POST"])
def password():
    """Password change"""

    if request.method == "POST":

        user_id = session["user_id"]

        password = request.form.get("password")
        hashed_password = generate_password_hash(password)
        # Ensures if password is submitted
        if not password:
            return apology("Please enter a password")

        db.execute("UPDATE users SET hash = ? WHERE id = ?", hashed_password, user_id)
        return redirect("/login")
    else:
        return render_template("password.html")
