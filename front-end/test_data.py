import os

from system_automation import db, User


if __name__ == "__main__":
    if os.path.isfile("test_db.sqlite"):
        os.remove("test_db.sqlite")
    db.create_all()

    user = User("test", "test")
    db.session.add(user)
    db.session.commit()

