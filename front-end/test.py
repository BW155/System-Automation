
import time
import socket
import binascii
import json
import math


PYTHON_TCP_IP = '192.168.2.180'
PYTHON_TCP_PORT = 9001

WEMOS_TCP_IP = '192.168.2.183'
WEMOS_TCP_PORT = 8080

BUFFER_SIZE = 1024

ips = {}

def millis():
    millis = int(round(time.time() * 1000))
    return millis


def routine():
    data = send(PYTHON_TCP_IP, PYTHON_TCP_PORT, json.dumps({"type": 2, "id": 1}))
    data = json.loads(data)
    actuators = {"led": data["actuators"]["led"]}
    data = send(WEMOS_TCP_IP, WEMOS_TCP_PORT, json.dumps({"id": 1, "actuators": actuators}))
    data = json.loads(data)
    print(data)
    data = send(PYTHON_TCP_IP, PYTHON_TCP_PORT, json.dumps({"id": 1, "sensors": data["sensors"], "actuators": actuators}))
    print(data)
    print()


def send(ip, port, message):
    #try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(0.5)
    s.connect((ip, port))
    message = bytes(message)
    s.send(message)
    data = s.recv(BUFFER_SIZE)
    s.close()
    return data
    #except Exception as e:
    #    print("exception: ", e)
    #    return ""

if __name__ == "__main__":
    while 1:
        routine()
        time.sleep(0.1)

