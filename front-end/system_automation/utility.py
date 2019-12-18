from system_automation import User, 
from flask import current_user

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

