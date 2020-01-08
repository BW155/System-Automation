from system_automation import User
from flask_login import current_user
from functools import wraps
import flask

def roles_allowed(roles=list()):
    def decorator(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            user = current_user

            if user is not None and user.role in roles:
                return f(*args, **kwargs)

            flask.flash("Geen toegang", "error")
            return flask.redirect(flask.url_for("index"))
        return decorated_function
    return decorator

