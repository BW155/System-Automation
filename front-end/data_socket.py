import threading
from time import sleep
import socket
import json
from json import JSONDecodeError
from system_automation.objects import objects, set_objects, check_objects_change

bind_ip = '0.0.0.0'
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
    server.listen(10)

    while 1:
        print("accepting")
        conn, addr = server.accept()
        print("accepted: {}".format(addr))
        print("receiving")
        data = conn.recv(BUFFER_SIZE)
        print("received")
        if not data: break
        message = data.decode('utf-8')
        print("received data: ", message)
        resp = process_message(message)
        print("sending")
        conn.send(bytes(resp, "utf-8"))
        print("send")
        conn.close()
        print("closed")


def process_message(message):
    global objects
    js = None
    try:
        js = json.loads(message)
    except JSONDecodeError:
        return "JSONError"

    messsage_type = js.get("type")

    if not messsage_type:
        return "Error"

    if messsage_type == 1:
        return "1" if check_objects_change() else "0"

    if messsage_type == 2:
        obj_id = js.get("id")
        if obj_id and obj_id >= 1 and obj_id <= 7:
            return json.dumps([i for i in objects if i["id"] == obj_id][0])

    if messsage_type == 3:
        data = js.get("data")
        if data:
            set_objects(data)
            return "1"
        else:
            return "0"

    return "UNKOWN"


def start_data_socket_thread():
    t = threading.Thread(target=data_socket_routine)
    t.daemon = True
    t.start()

