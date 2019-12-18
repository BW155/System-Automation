from system_automation import app
from data_socket import start_data_socket_thread


if __name__ == '__main__':
    start_data_socket_thread()
    app.run(host="0.0.0.0", port=8000, debug=True, use_reloader=False)

