import os

from uuid import uuid4
from passlib.hash import argon2

from flask_login import UserMixin
from flask_sqlalchemy import SQLAlchemy

from system_automation import app, db


class Model(db.Model):
    """Base Model class that includes convenience methods."""
    __abstract__ = True
    id = db.Column(db.Integer, primary_key=True)


class User(Model, UserMixin):
    username = db.Column(db.String, unique=True)
    password = db.Column(db.String)

    def __init__(self, username, password):
        self.username = username
        self.password = argon2.hash(password)

    def verify_password(self, password):
        return argon2.verify(password, self.password)

