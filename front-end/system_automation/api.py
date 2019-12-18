import flask
from flask_login import login_required, login_user, logout_user
from . import app, User, Role, data
import json


# api route for logged-in users
@app.route("/api/data", methods=["POST", "GET"])
@login_required
def data():
    return ""


# api route for non-logged-in users
@app.route("/api/basic_data", methods=["POST", "GET"])
def basic_data():
    return ""
