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

    # Update fund record from MyInvestor
    FUNDS.update()
    
    if request.method == 'POST':
        # TODO: check if portfolio sums to 100%
        # TODO: store in db
        return request.form

    return render_template("ideal-portfolio.html", user=current_user, funds=FUNDS.basic)
