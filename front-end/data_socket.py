import threading
from time import sleep
import socket
import json
from system_automation.objects import objects

bind_ip = '127.0.0.1'
bind_port = 9001
BUFFER_SIZE = 1200


"""
Type:
1 = Change Check
2 = Give Actuator Values
3 = Receive All
"""
def data_socket_routine():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    server.bind((bind_ip, bind_port))
    server.listen(1)

    while 1:
        conn, addr = server.accept()
        data = conn.recv(BUFFER_SIZE)
        if not data: break
        data = data.decode('utf-8')
        print("received data: ", data)
        resp = process_message(data)
        conn.send(bytes(resp, "utf-8"))
        sleep(0.5) # sleep 1 second


def process_message(message):
    global objects
    message = json.loads(message)
    messsage_type = message.get("type")

    if not messsage_type:
        return "Error"

    if messsage_type == 1:
        return "1"

    if messsage_type == 2:
        return json.dumps(objects)

    if messsage_type == 3:
        objects = message["data"]
        return "1"


def start_data_socket_thread():
    t = threading.Thread(target=data_socket_routine)
    t.daemon = True
    t.start()

