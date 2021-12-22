from . import db
from flask_login import UserMixin
from sqlalchemy.sql import func

MAX_LEN = 128


class Funds(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    fund_name = db.Column(db.String(1000))
    fund_isin = db.Column(db.String(100))
    fund_allocation = db.Column(db.Integer)


class User(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(MAX_LEN), unique=True)
    password = db.Column(db.String(MAX_LEN))


class UserWithFund(db.Model):
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'))
    fund_id = db.Column(db.Integer, db.ForeignKey('fund.id'))
    
