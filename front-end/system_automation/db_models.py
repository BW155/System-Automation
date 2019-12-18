import os
import enum

from uuid import uuid4
from passlib.hash import argon2

from flask_login import UserMixin
from flask_sqlalchemy import SQLAlchemy

from system_automation import app, db


class Role(enum.Enum):
    PARENT = "PARENT"
    GUARD = "GUARD"


class Model(db.Model):
    """Base Model class that includes convenience methods."""
    __abstract__ = True
    id = db.Column(db.Integer, primary_key=True)


class User(Model, UserMixin):
    username = db.Column(db.String, unique=True)
    password = db.Column(db.String)
    role = db.Column(db.Enum(Role))

    def __init__(self, username, password, role):
        self.username = username
        self.password = argon2.hash(password)
        self.role = role

    def verify_password(self, password):
        return argon2.verify(password, self.password)

