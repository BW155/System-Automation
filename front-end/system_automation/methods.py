import flask
from flask_login import login_required, login_user, logout_user
from . import app, User
import system_automation.objects as objects
from .objects import web_translate_objects
from .api import notifications


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
            return flask.redirect(flask.url_for("interface"))
        else:
            flask.flash("Gebruikersnaam of Wachtwoord verkeerd", "error")
    return flask.render_template("login.html")


@app.route("/logout")
@login_required
def logout():
    logout_user()
    flask.flash("Uitgelogd", "good")
    return flask.redirect(flask.url_for("index"))


@app.route("/dashboard")
@login_required
def interface():
    return flask.render_template("dashboard.html", objects=web_translate_objects(), last_not_id=notifications[-1]["not_id"] if len(notifications) > 0 else -1)
