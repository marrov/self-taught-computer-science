from . import db

from flask_login import login_required, current_user
from flask import Blueprint, render_template, request, flash, jsonify

views = Blueprint('views', __name__)


@views.route('/', methods=['GET', 'POST'])
@login_required
def home():
    """ Loads landing page"""
    return render_template("home.html", user=current_user)
