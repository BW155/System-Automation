import os
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager, login_required
from . import config

basedir = os.getcwd()

app = Flask(__name__, template_folder=basedir + "/templates/", static_url_path='/static/', static_folder=basedir + '/static/',)
app.config.from_object(os.environ['APP_SETTINGS'])

db = SQLAlchemy(app)

login_manager = LoginManager()
login_manager.init_app(app)


from .db_models import User, Role
from .methods import index, login
from .api import dashboard_api, interface_api, interface_notifications, interface_notifications_post, dashboard_api_all


@login_manager.user_loader
def load_user(user_id):
    return User.query.get(user_id)

