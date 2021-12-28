from . import db, FUNDS
from .models import IdealPortfolio, RealPortfolio, Fund

from flask_login import login_required, current_user
from flask import Blueprint, render_template, request, flash, redirect, url_for

views = Blueprint('views', __name__)


@views.route('/', methods=['GET'])
def home():
    """Loads landing page"""
    return render_template("home.html", user=current_user)


@views.route('/dashboard', methods=['GET'])
@login_required
def dashboard():
    """Logic for main dashboard"""

    # Update fund record from MyInvestor API
    FUNDS.update()

    # Check if user has an ideal and/or real portfolio
    ideal_portfolio_exists = (IdealPortfolio.query.filter_by(user_id = current_user.id).first() is not None)
    real_portfolio_exists = (RealPortfolio.query.filter_by(user_id = current_user.id).first() is not None)

    if real_portfolio_exists and ideal_portfolio_exists:
        # TODO: Get real and ideal allocation and (maybe?) calculate the difference
        # TODO: get total invested ammount from current user
        # TODO: calculate rebalance as diff_fund * total_invested (maybe in html not here)
        # TODO: Assess what a reasonable threshold for rebalancing (maybe three tier: green (<2%) - yellow (3% to 5%) - red (>10%))

        # Get the current user's funds from ideal portfolio
        idealportfolio = IdealPortfolio.query.filter_by(user_id=current_user.id).all()
        fund_ids = [item.fund_id for item in idealportfolio]
        funds = []
        for fund_id in fund_ids:
            funds.append(Fund.query.filter_by(id=fund_id).first().isin)

        # Get funds' names from raw data through isin into a list
        names = []
        for fund in funds:
            names.append(
                next(item for item in FUNDS.raw if item["codigoIsin"] == fund)["nombre"])

        # Get the current user's  real and ideal allocations
        realportfolio = RealPortfolio.query.filter_by(user_id=current_user.id).all()
        real_allocations = [item.allocation for item in realportfolio]
        ideal_allocations = [item.allocation for item in idealportfolio]

        return render_template("dashboard.html", user=current_user, max_difference = 2, real_portfolio_exists=real_portfolio_exists, ideal_portfolio_exists=ideal_portfolio_exists)

    return render_template("dashboard.html", user=current_user, real_portfolio_exists = real_portfolio_exists, ideal_portfolio_exists = ideal_portfolio_exists)


@views.route('/real-portfolio', methods=['GET', 'POST'])
@login_required
def real_portfolio():
    """Logic for real iportfolio"""

    # Update fund record from MyInvestor API
    FUNDS.update()

    # Check if user has an ideal and/or real portfolio
    ideal_portfolio_exists = (IdealPortfolio.query.filter_by(user_id = current_user.id).first() is not None)
    real_portfolio_exists = (RealPortfolio.query.filter_by(user_id = current_user.id).first() is not None)

    if ideal_portfolio_exists:

        # Get the current user's funds from ideal portfolio
        idealportfolio = IdealPortfolio.query.filter_by(user_id = current_user.id).all()
        fund_ids = [item.fund_id for item in idealportfolio]
        funds = []
        for fund_id in fund_ids:
            funds.append(Fund.query.filter_by(id = fund_id).first().isin)

        # Get funds' names from raw data through isin into a list
        names = [];
        for fund in funds:
            names.append(
                next(item for item in FUNDS.raw if item["codigoIsin"] == fund)["nombre"])

        if real_portfolio_exists:

            # Get the current user's  real and ideal allocations
            realportfolio = RealPortfolio.query.filter_by(user_id = current_user.id).all()
            real_allocations = [item.allocation for item in realportfolio]
            ideal_allocations = [item.allocation for item in idealportfolio]

            if request.method == 'POST':
                # Delete saved real portfolio

                # Delete relationship between user and funds
                for item in realportfolio:
                    db.session.delete(item)
                db.session.commit()

                flash('Portfolio deleted successfully', category='success')
                return redirect(url_for('views.real_portfolio'))

                return "delete saved real portfolio"
            else:
                # Show real portfolio
                return render_template("real-portfolio.html", user=current_user, user_data=zip(funds, names, real_allocations, ideal_allocations), real_portfolio_exists = real_portfolio_exists, ideal_portfolio_exists = ideal_portfolio_exists)
        else:
            if request.method == 'POST':
                # store real portfolio that user has just defined
                
                # Get form data into list
                n_assets = len(request.form)
                ammounts = []
                for i in range(n_assets):
                    ammounts.append(float(request.form.get('ammount-' + str(i))))
                allocations = [round(100*(ammount/sum(ammounts)), 2) for ammount in ammounts]

                # HACK: ensures that sum of allocations is allways 100%
                allocations[-1] = 100 - sum(allocations[0:-1])

                #TODO: set invested to zero if user deletes real portfolio

                # Check if real portfolio allocations sum to 100%
                if sum(allocations) != 100:
                    flash('Asset allocations must sum to 100%', category='error')
                else:
                    # Store real portfolio relationship in database
                    for (fund, allocation) in zip(funds, allocations):
                        #if not Fund.query.filter_by(isin=fund).first():
                        db.session.add(RealPortfolio(user_real=current_user, fund_real=Fund.query.filter_by(
                            isin=fund).first(), allocation=allocation))

                    # Store user sum of ammount invested in User so that only allocations are necessary
                    current_user.invested = sum(ammounts)
                    db.session.commit()

                    flash('Portfolio created successfully', category='success')
                
                return redirect(url_for('views.real_portfolio'))
            else:
                # Show real portfolio builder
                return render_template("real-portfolio.html", user=current_user, user_data = zip(funds, names), real_portfolio_exists = real_portfolio_exists, ideal_portfolio_exists = ideal_portfolio_exists)
    else:
        # Show danger card instructing user to make an ideal portfolio first
        return render_template("real-portfolio.html", user=current_user, real_portfolio_exists = real_portfolio_exists, ideal_portfolio_exists = ideal_portfolio_exists)

@views.route('/ideal-portfolio', methods=['GET', 'POST'])
@login_required
def ideal_portfolio():
    """Logic for ideal portfolio"""

    # Update fund record from MyInvestor API
    FUNDS.update()

    # Check if user has an ideal and/or real portfolio
    ideal_portfolio_exists = (IdealPortfolio.query.filter_by(user_id = current_user.id).first() is not None)
    real_portfolio_exists = (RealPortfolio.query.filter_by(user_id = current_user.id).first() is not None)

    if ideal_portfolio_exists:

        # Get the current user's funds and allocations stored in the databases
        idealportfolio = IdealPortfolio.query.filter_by(user_id = current_user.id).all()
        allocations = [item.allocation for item in idealportfolio]
        fund_ids = [item.fund_id for item in idealportfolio]
        funds = []
        for fund_id in fund_ids:
            funds.append(Fund.query.filter_by(id = fund_id).first().isin)

        # IF POST, delete sotred ideal portfolio
        if request.method == 'POST':
            
            if real_portfolio_exists:
                flash('Delete your real portfolio before deleting your ideal portfolio', category='error')
            else:
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

        # Get fund data for displaying portfolio from raw data through isin into lists
        names = []; 
        for fund in funds:
            names.append(
                next(item for item in FUNDS.raw if item["codigoIsin"] == fund)["nombre"])

        # Otherwise (i.e. GET), show user's portfolio
        return render_template('ideal-portfolio.html', user=current_user, user_data=zip(funds, names, allocations), ideal_portfolio_exists=ideal_portfolio_exists)

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

                # Store ideal portfolio relationship in database
                for (fund, allocation) in zip(funds, allocations):
                    #if not Fund.query.filter_by(isin=fund).first():
                    db.session.add(IdealPortfolio(user_ideal=current_user, fund_ideal=Fund.query.filter_by(
                        isin=fund).first(), allocation=allocation))
                db.session.commit()

                flash('Portfolio created successfully', category='success')
                return redirect(url_for('views.ideal_portfolio'))
        
        return render_template('ideal-portfolio.html', user=current_user, funds=FUNDS.basic, ideal_portfolio_exists=ideal_portfolio_exists)
