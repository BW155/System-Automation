from flask import Flask, flash, redirect, render_template, request, session, abort
import flask
import os
from flask_sqlalchemy import SQLAlchemy
from system_automation import app, login_manager, User
from data_socket import start_data_socket_thread


if __name__ == '__main__':
    start_data_socket_thread()
    app.run(host="0.0.0.0", port=8000, debug=True)

