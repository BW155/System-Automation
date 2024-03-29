import threading
from time import sleep
import socket
import socketserver
import json
from json import JSONDecodeError
from system_automation.objects import objects, set_object, check_objects_change
from system_automation.api import add_notification
from system_automation.methods import set_medicine_button

bind_ip = '0.0.0.0'
bind_port = 9001
BUFFER_SIZE = 1200

pi_notification_templates = {
    0: "Mogelijk heeft timmothy een epileptische aanval",
    1: "Timothy wil de deur openen",
    2: "Iemand belt aan",
    3: "Timothy is uit bed",
    4: "Koelkast is open",
    5: "Medicijnen 09:00",
    6: "Medicijnen 13:00",
    7: "Medicijnen 18:00",
    8: "Medicijnen 23:00",
    9: "Alarm, Timothy heeft hulp nodig"
}

class PiSocketServer(socketserver.BaseRequestHandler):

    def handle(self):
        # self.request is the TCP socket connected to the client
        self.data = self.request.recv(1024).strip()
        print("{} wrote:".format(self.client_address[0]))
        print(self.data)
        response = process_message(self.data.decode("utf-8"))
        # just send back the same data, but upper-cased
        self.request.sendall(bytes(response, "utf-8"))
        print("END\n")


def data_socket_routine():
    # Create the server, binding to localhost on port 9999
    with socketserver.TCPServer((bind_ip, bind_port), PiSocketServer) as server:
        # Activate the server; this will keep running until you
        # interrupt the program with Ctrl-C
        server.serve_forever()


def process_message(message):
    global objects
    try:
        js = json.loads(message)

        messsage_type = js.get("type")

        if not messsage_type:
            return "Error"

        """
        Type:
        1 = Change Check
        2 = Give Actuator Values
        3 = Receive All
        4 = Notification
        """
        if messsage_type == 1:
            obj_id = js.get("id")
            if obj_id and obj_id >= 1 and obj_id <= 7:
                return check_objects_change(obj_id)
            return "UNKOWN ID"

        if messsage_type == 2:
            obj_id = js.get("id")
            if obj_id and obj_id >= 1 and obj_id <= 7:
                data = dict([i for i in objects if i["id"] == obj_id][0]).copy()
                del data["sensors"]
                return json.dumps(data)
            return "UNKOWN ID"

        if messsage_type == 3:
            if js:
                del js["type"]
                set_object(js)
                if js["id"] == 4:
                    if js["sensors"]["button"] == 1:
                        add_notification(10, "NOODKNOP INGEDRUKT");
                return "1"
            return "0"

        if messsage_type == 4:
            n_id = js.get("id")
            notification = pi_notification_templates[n_id]
            if notification is not None:
                if n_id >= 5 and n_id <= 8:
                    set_medicine_button()
                add_notification(n_id, None, notification)
                return "1"
            return "0"


        return "UNKOWN"
    except JSONDecodeError as e:
        print(e)
        return "JSONError"


def start_data_socket_thread():
    t = threading.Thread(target=data_socket_routine)
    t.start()

