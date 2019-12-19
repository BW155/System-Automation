import flask
from flask_login import login_required, login_user, logout_user
from . import app, User, Role
from .objects import get_actuator, process_actuator
from .utility import roles_allowed
import json

notification_templates = [{"title": "Alarm", "message": "Er is hulp nodig!!!"}, {"title": "Naar Buiten", "message": "Patient wil naar buiten"}]
notifications = []

# api route for logged-in users
@app.route("/api/dashboard/<int:obj_id>", methods=["POST", "GET"])
@login_required
def dashboard_api(obj_id):
    return ""


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
        notifications.append(notification_templates[0])
    if notif_type == 1:
        notifications.append(notification_templates[1])


@app.route("/api/interface_notifications/", methods=["GET"])
@login_required
@roles_allowed([Role.GUARD])
def interface_notifications():
    global notifications
    notifs_to_send = notifications
    notifications = []
    return json.dumps(notifs_to_send)

