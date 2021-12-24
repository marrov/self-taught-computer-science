from . import db
from flask_login import UserMixin

MAX_LEN = 128


class IdealPortfolio(db.Model):
    __tablename__ = 'idealportfolio'
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'), primary_key=True)
    fund_id = db.Column(db.Integer, db.ForeignKey('fund.id'), primary_key=True)
    allocation = db.Column(db.Integer)
    fund_ideal = db.relationship("Fund", back_populates="users_ideal")
    user_ideal = db.relationship("User", back_populates="funds_ideal")


class RealPortfolio(db.Model):
    __tablename__ = 'realportfolio'
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'), primary_key=True)
    fund_id = db.Column(db.Integer, db.ForeignKey('fund.id'), primary_key=True)
    allocation = db.Column(db.Integer)
    fund_real = db.relationship("Fund", back_populates="users_real")
    user_real = db.relationship("User", back_populates="funds_real")


class User(db.Model, UserMixin):
    __tablename__ = 'user'
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(MAX_LEN), unique=True)
    invested = db.Column(db.Real, deafult=0)
    password = db.Column(db.String(MAX_LEN))
    funds_ideal = db.relationship("IdealPortfolio", back_populates="user_ideal")
    funds_real = db.relationship("RealPortfolio", back_populates="user_real")


class Fund(db.Model):
    __tablename__ = 'fund'
    id = db.Column(db.Integer, primary_key=True)
    isin = db.Column(db.String(20), unique=True)
    users_ideal = db.relationship("IdealPortfolio", back_populates="fund_ideal")
    users_real = db.relationship("RealPortfolio", back_populates="fund_real")
