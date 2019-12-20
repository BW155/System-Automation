from system_automation import User
from flask_login import current_user
from functools import wraps

def roles_allowed(roles=list()):
    def decorator(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            user = current_user

            if user is not None and user.role in roles:
                return f(*args, **kwargs)

            raise NotAuthorized()
        return decorated_function
    return decorator

