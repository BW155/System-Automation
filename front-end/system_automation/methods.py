import time

import flask
from flask_login import login_required, login_user, logout_user, current_user

from . import app, User, Role
from .objects import web_translate_objects, set_actuator
import system_automation.objects as objects
from .api import notifications
from .utility import roles_allowed

@app.context_processor
def inject_cur_time():
    return {"cur_time": time.time()}

@app.route("/")
def index():
    return flask.render_template("index.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    if flask.request.method == "POST":
        username = flask.request.form.get("username")
        password = flask.request.form.get("password")

        user = User.query.filter_by(username=username).first()
        if user is not None and user.verify_password(password):
            login_user(user)

            flask.flash("Logged in successfully.", "good")
            if user.role == Role.GUARD:
                return flask.redirect(flask.url_for("guard_interface"))
            elif user.role == Role.PARENT:
                return flask.redirect(flask.url_for("parent_interface"))
            else:
                flask.flash("Geen toegang", "error")
                return flask.redirect(flask.url_for("index"))
        else:
            flask.flash("Gebruikersnaam of Wachtwoord verkeerd", "error")
    return flask.render_template("login.html")


@app.route("/logout")
@login_required
def logout():
    logout_user()
    flask.flash("Uitgelogd", "good")
    return flask.redirect(flask.url_for("index"))


@app.route("/guard_interface")
@login_required
@roles_allowed([Role.GUARD])
def guard_interface():
    return flask.render_template("guard_interface.html", objects=web_translate_objects(), role=current_user.role)


@app.route("/parent_interface", methods=["GET", "POST"])
@login_required
@roles_allowed([Role.PARENT])
def parent_interface():
    if flask.request.method == "POST":
        door = flask.request.form.get("door")

        if door.isdigit():
            set_actuator(7, "servo", door)
            flask.flash("Successvol Aangepast", "good")
            return flask.redirect(flask.url_for("logout"))
        flask.flash("Ongeldige deur waarde", "error")

    return flask.render_template("parent_interface.html")

