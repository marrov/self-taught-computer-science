from . import db
from flask_login import UserMixin

MAX_LEN = 128


class UserWithFund(db.Model):
    __tablename__ = 'userwithfund'
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'), primary_key=True)
    fund_id = db.Column(db.Integer, db.ForeignKey('fund.id'), primary_key=True)
    allocation = db.Column(db.Integer)
    fund = db.relationship("Fund", back_populates="users")
    user = db.relationship("User", back_populates="funds")


class User(db.Model, UserMixin):
    __tablename__ = 'user'
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(MAX_LEN), unique=True)
    password = db.Column(db.String(MAX_LEN))
    funds = db.relationship("UserWithFund", back_populates="user")


class Fund(db.Model):
    __tablename__ = 'fund'
    id = db.Column(db.Integer, primary_key=True)
    fund_isin = db.Column(db.String(20), unique=True)
    users = db.relationship("UserWithFund", back_populates="fund")
