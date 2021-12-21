from . import db, FUNDS

from flask_login import login_required, current_user
from flask import Blueprint, render_template, request, flash, jsonify

views = Blueprint('views', __name__)


@views.route('/', methods=['GET'])
def home():
    """Loads landing page"""
    return render_template("home.html", user=current_user)


@views.route('/dashboard', methods=['GET', 'POST'])
@login_required
def dashboard():
    """Logic for main dashboard"""
    return render_template("dashboard.html", user=current_user)

@views.route('/ideal-portfolio', methods=['GET', 'POST'])
#@login_required
def ideal_portfolio():
    """Logic for ideal portfolio"""
    FUNDS.update()
    return render_template("ideal-portfolio.html", user=current_user, funds=FUNDS.clean)


@views.route('/query', methods=['GET'])
@login_required
def query():
    FUNDS.update()
    return FUNDS.clean[0]
