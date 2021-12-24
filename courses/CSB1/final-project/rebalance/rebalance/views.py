from . import db, FUNDS
from .models import IdealPortfolio, Fund

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


@views.route('/real-portfolio', methods=['GET', 'POST'])
@login_required
def real_portfolio():
    """Logic for real iportfolio"""

    # Check if user has an ideal portfolio
    ideal_portfolio_exists = (IdealPortfolio.query.filter_by(user_id = current_user.id).first() is not None)

    # Check if user has a reak portfolio
    real_portfolio_exists = False

    return render_template("real-portfolio.html", user=current_user, real_portfolio_exists = real_portfolio_exists, ideal_portfolio_exists = ideal_portfolio_exists)

@views.route('/ideal-portfolio', methods=['GET', 'POST'])
@login_required
def ideal_portfolio():
    """Logic for ideal portfolio"""

    # Update fund record from MyInvestor API
    FUNDS.update()

    # Check if user already has an ideal portfolio
    ideal_portfolio_exists = (IdealPortfolio.query.filter_by(user_id = current_user.id).first() is not None)

    if ideal_portfolio_exists:

        # Get the current user's funds and allocations stored in the databases
        idealportfolio = IdealPortfolio.query.filter_by(user_id = current_user.id).all()
        allocations = [item.allocation for item in idealportfolio]
        fund_ids = [item.fund_id for item in idealportfolio]
        funds = []
        for fund_id in fund_ids:
            funds.append(Fund.query.filter_by(id = fund_id).first().isin)

        # Get other info for display of user's funds (e.g. fund name)

        # IF POST, delete sotred ideal portfolio
        if request.method == 'POST':

            # Delete relationship between user and funds
            for item in idealportfolio:
                db.session.delete(item)
            db.session.commit()

            # Delete funds that are not being owned by any user
            # Retrieve all unique fund ids in idealportfolios database into list
            owned_fund_ids = [item.fund_id for item in IdealPortfolio.query.all()]

            # Get fund items from Fund database
            stored_funds = Fund.query.all()

            # Delete all funds from B not in A
            for stored_fund in stored_funds:
                if stored_fund.id not in owned_fund_ids:
                    db.session.delete(stored_fund)
            db.session.commit()

            flash('Portfolio deleted successfully', category='success')
            return redirect(url_for('views.ideal_portfolio'))

        # Get fund data from raw data through isin into lists
        names = [];  urls = []; categories = []; ter = []
        for fund in funds:
            names.append(
                next(item for item in FUNDS.raw if item["codigoIsin"] == fund)["nombre"])
            urls.append(
                next(item for item in FUNDS.raw if item["codigoIsin"] == fund)["urlKiid"])

        # Otherwise (i.e. GET), show user's portfolio
        return render_template('ideal-portfolio.html', user=current_user, user_data=zip(funds, names, urls, allocations), ideal_portfolio_exists=ideal_portfolio_exists)

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
                    db.session.add(IdealPortfolio(user=current_user, fund=Fund.query.filter_by(
                        isin=fund).first(), allocation=allocation))
                db.session.commit()

                flash('Portfolio created successfully', category='success')
                return redirect(url_for('views.ideal_portfolio'))
        
        return render_template('ideal-portfolio.html', user=current_user, funds=FUNDS.basic, ideal_portfolio_exists=ideal_portfolio_exists)
