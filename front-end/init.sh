python3 -m pip install virtualenv
python3 -m virtualenv venv
. venv/bin/activate
python -m pip install -r requirements.txt
. ./.env_dev
python test_data.py
