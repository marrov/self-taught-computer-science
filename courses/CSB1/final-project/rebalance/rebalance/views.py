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
        # Get number of assets 
        n_assets = int(len(request.form)/2)

        # Get form data into lists
        allocations = []
        funds = []
        for i in range(n_assets):
            allocations.append(float(request.form.get('allocation-' + str(i))))
            funds.append(request.form.get('funds-' + str(i)))

        # Check if portfolio allocations sum to 100% and if all funds are unique
        if sum(allocations) != 100:
            flash('Asset allocations must sum to 100%', category='error')
        elif len(funds) > len(set(funds)):
            flash('All assets must be unique', category='error')

        # TODO: store in db

        return request.form

    return render_template("ideal-portfolio.html", user=current_user, funds=FUNDS.basic)
