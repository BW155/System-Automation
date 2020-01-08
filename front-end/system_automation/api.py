import flask
from flask_login import login_required, login_user, logout_user
from . import app, User, Role
from .objects import get_actuator, process_actuator, set_actuator, get_objects
from .utility import roles_allowed
import json
import time
from datetime import datetime


notification_templates = [
    {"id": 0, "time": "", "title": "Alarm", "message": "Er is hulp nodig!!!"},
    {"id": 1, "time": "", "title": "Naar Buiten", "message": "Patient wil naar buiten"}
]


notifications = []


def add_notification(n_id, title, notification):
    global notifications
    notifications.append({"id": n_id, "title": title, "message": notification})


# api route for logged-in users
@app.route("/api/dashboard/<int:obj_id>", methods=["POST", "GET"])
@login_required
@roles_allowed([Role.GUARD, Role.PARENT])
def dashboard_api(obj_id):
    if flask.request.method == "POST":
        actuator = flask.request.form.get("actuator")
        value = flask.request.form.get("value")
        return set_actuator(obj_id, actuator, value)
    if flask.request.method == "GET":
        actuator = flask.request.form.get("actuator")
        return get_actuator(obj_id, actuator)


# api route for logged-in users to get objects
@app.route("/api/dashboard/all", methods=["GET"])
@login_required
@roles_allowed([Role.GUARD, Role.PARENT])
def dashboard_api_all():
    return get_objects()


# api route for non-logged-in users
@app.route("/api/interface/<action>", methods=["POST"])
def interface_api(action):
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

@app.route("/api/interface_notifications/<int:notif_type>", methods=["POST"])
def interface_notifications_post(notif_type):
    global notifications

    if notif_type == 0:
        notif = notification_templates[0]
        notif["time"] = datetime.now().strftime("%d-%m-%Y %H:%M:%S")
        notif["not_id"] = len(notifications)
        notifications.append(notif.copy())
    elif notif_type == 1:
        notif = notification_templates[1]
        notif["time"] = datetime.now().strftime("%d-%m-%Y %H:%M:%S")
        notif["not_id"] = len(notifications)
        notifications.append(notif.copy())
    else:
        return "0"
    return "1"


@app.route("/api/interface_notifications", methods=["GET"])
@login_required
@roles_allowed([Role.GUARD])
def interface_notifications():
    cur_time = time.time()

    while len(notifications) == 0:
        time.sleep(0.1)
        if time.time() - cur_time >= 9:
            return "TimeOut", 308

    cur_notifications = notifications.copy()
    del notifications[:]
    return json.dumps(cur_notifications)

