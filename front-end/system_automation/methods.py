import flask
from flask_login import login_required, login_user, logout_user
from . import app, User


objects = [
    {"name": "Bed"},
    {"name": "Stoel"},
    {"name": "Zuil"},
    {"name": "Koelkast"},
    {"name": "Deur", "buttons": [{"item_id": 1, "text": "open/dicht"}], "sensors": [{"name": "Is open", "value": False}]},
    {"name": "Tafel Lamp"},
    {"name": "Muur"}
]


@app.route("/")
def index():
    return flask.render_template("index.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    # Here we use a class of some kind to represent and validate our
    # client-side form data. For example, WTForms is a library that will
    # handle this for us, and we use a custom LoginForm to validate.
    if flask.request.method == "POST":
        username = flask.request.form["username"]
        password = flask.request.form["password"]

        user = User.query.filter_by(username=username).first()
        if user is not None and user.verify_password(password):
            # Login and validate the user.
            # user should be an instance of your `User` class
            login_user(user)

            flask.flash("Logged in successfully.")

            return flask.redirect(flask.url_for("interface"))
        else:
            return "Error"
    return flask.render_template("login.html")


@app.route("/logout")
@login_required
def logout():
    logout_user()
    return flask.redirect(flask.url_for("index"))


@app.route("/dashboard")
@login_required
def interface():
    return flask.render_template("dashboard.html", objects=objects)


