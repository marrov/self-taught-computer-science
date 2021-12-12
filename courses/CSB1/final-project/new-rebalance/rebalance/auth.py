from . import db
from .models import User
from flask import Blueprint, render_template, request, flash, redirect, url_for
from flask_login import login_user, login_required, logout_user, current_user
from werkzeug.security import generate_password_hash, check_password_hash, safe_str_cmp

auth = Blueprint('auth', __name__)

MAX_LEN = 128
MIN_USER_LEN = 4
MIN_PASS_LEN = 8


@auth.route('/login', methods=['GET', 'POST'])
def login():
    """Log user in"""

    if request.method == 'POST':

        # Retrieve variables from POST form
        username = request.form.get('username')
        password = request.form.get('password')

        # Query the database for the user
        user = User.query.filter_by(username=username).first()

        # Check unsername and password and login if correct
        if user:
            if check_password_hash(user.password, password):
                login_user(user, remember=True)
                return redirect(url_for('views.home'))
            else:
                flash('Invalid password', category='error')
        else:
            flash('Invalid username', category='error')

    return render_template("login.html", user=current_user)


@auth.route('/logout')
@login_required
def logout():
    """Log user out"""

    logout_user()
    return redirect(url_for('views.home'))


@auth.route('/register', methods=['GET', 'POST'])
def register():
    """Register new user"""

    if request.method == 'POST':

        # Retrieve variables from POST form
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')

        # Query the database for the user
        user = User.query.filter_by(username=username).first()

        if user:
            flash('Username already exists.', category='error')
        elif len(username) < MIN_USER_LEN or len(username) > MAX_LEN:
            flash(
                f'Username must be between {MIN_USER_LEN} and {MAX_LEN} characters', category='error')
        elif not safe_str_cmp(password, confirmation):
            flash('Passwords do not match', category='error')
        elif len(username) < MIN_PASS_LEN or len(username) > MAX_LEN:
            flash(
                f'Password must be between {MIN_PASS_LEN} and {MAX_LEN} characters', category='error')
        else:
            # Add new user to the database
            new_user = User(username=username, password=generate_password_hash(password))
            db.session.add(new_user)
            db.session.commit()

            # Flash success alert and redirect to login
            flash('Account created successfully', category='success')
            return redirect(url_for('auth.login'))

    return render_template("register.html", user=current_user)
