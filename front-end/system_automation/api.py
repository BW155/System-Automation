import flask
from flask_login import login_required, login_user, logout_user
from . import app, User, Role
from .objects import get_actuator, process_actuator
import json


# api route for logged-in users
@app.route("/api/dashboard/<int:obj_id>", methods=["POST", "GET"])
@login_required
def dashboard_api(obj_id):
    return ""


# api route for non-logged-in users
@app.route("/api/basic_interface/<action>", methods=["POST"])
def basic_interface_api(action):
    allowed = ["1,led", "2,led", "3,led", "4,led", "5,led", "7,led1"]
    if action not in allowed:
        return "-1"

    parts = action.split(",")
    if len(parts) == 2:
        obj_id = parts[0]
        if obj_id.isdigit():
            val = get_actuator(int(obj_id), parts[1])
            if val is not None:
                process_actuator(int(obj_id), parts[1])
                return "1"
    return "0"

