from . import db, FUNDS
from .models import User, UserWithFund, Fund

from flask_login import login_required, current_user
from flask import Blueprint, render_template, request, flash, redirect, url_for

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
@login_required
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
            funds.append(request.form.get('fund-' + str(i)))

        # Check if portfolio allocations sum to 100% and if all funds are unique
        if sum(allocations) != 100:
            flash('Asset allocations must sum to 100%', category='error')
        elif len(funds) > len(set(funds)):
            flash('All assets must be unique', category='error')

        # Store new funds in database
        for fund in funds:
            if not Fund.query.filter_by(isin = fund).first():
                db.session.add(Fund(isin = fund))
        db.session.commit()

        # Store user/fund relationship in database
        for (fund, allocation) in zip(funds, allocations):
            #if not Fund.query.filter_by(isin=fund).first():
            db.session.add(UserWithFund(user=current_user, fund=Fund.query.filter_by(
                isin=fund).first(), allocation=allocation))
        db.session.commit()

        fnd = Fund.query.first()

        return render_template('ideal-portfolio.html', user=current_user, funds=FUNDS.basic, user_funds=funds, user_allocations=allocations, fnd=fnd)

    return render_template('ideal-portfolio.html', user=current_user, funds=FUNDS.basic)
