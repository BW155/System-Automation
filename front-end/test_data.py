import os

from system_automation import db, User, Role


if __name__ == "__main__":
    if os.path.isfile("test_db.sqlite"):
        os.remove("test_db.sqlite")
    db.create_all()

    guard = User("guard", "test", Role.GUARD)
    parent = User("parent", "test", Role.PARENT)

    db.session.add(guard)
    db.session.add(parent)
    db.session.commit()

