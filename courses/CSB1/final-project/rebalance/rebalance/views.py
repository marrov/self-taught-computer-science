from . import db, FUNDS
from .models import UserWithFund, Fund

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

    # Update fund record from MyInvestor API
    FUNDS.update()

    # Check if user already has an ideal portfolio
    ideal_portfolio_exists = (UserWithFund.query.filter_by(user_id = current_user.id).first() != None)

    if ideal_portfolio_exists:

        # IF POST, delete ideal

        # Else (GET), show portfolio
        return render_template('ideal-portfolio.html', user=current_user, funds=FUNDS.basic, ideal_portfolio_exists=ideal_portfolio_exists)
    else:
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
            else:
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

                return redirect(url_for('views.ideal_portfolio'))
                
        return render_template('ideal-portfolio.html', user=current_user, funds=FUNDS.basic, ideal_portfolio_exists=ideal_portfolio_exists)
