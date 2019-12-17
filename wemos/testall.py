import time
import socket
import binascii
import json
import math
import _thread


TCP_IP = '192.168.2.'
TCP_PORT = 8080
BUFFER_SIZE = 1024

ips = {}

COMMANDS =  {
    "1": {"id": 1, "actuators": {"led": 1}},
    "2": {"id": 2, "actuators": {"vibrator": 1, "led": 1}},
    "3": {"id": 3, "actuators": {"led": 1}},
    "4": {"id": 4, "actuators": {"led": 1, "buzzer": 1}},
    "5": {"id": 5, "actuators": {"led": 1, "window": 1}},
    "6": {"id": 6, "actuators": {"cooling", 1}},
    "7": {"id": 7, "actuators": {"led1": 1, "led2": 1, "servo": 1}}
}

COMMANDSN =  {
    "1": {"id": 1, "actuators": {"led": 0}},
    "2": {"id": 2, "actuators": {"vibrator": 0, "led": 0}},
    "3": {"id": 3, "actuators": {"led": 0}},
    "4": {"id": 4, "actuators": {"led": 0, "buzzer": 0}},
    "5": {"id": 5, "actuators": {"led": 0, "window": 0}},
    "6": {"id": 6, "actuators": {"cooling", 0}},
    "7": {"id": 7, "actuators": {"led0": 0, "led2": 0, "servo": 0}}
}


def millis():
    millis = int(round(time.time() * 1000))
    return millis


def routine():
    HELLO = "hello"
    for i in range(180, 200):
        print()
        ip = TCP_IP + str(i)
        data = send(ip, HELLO)
        if data != "":
            ips[data.decode("utf-8")] = ip
            print("Found: ", data, " on ", ip)


    for i in ips:
        print()
        ip = ips[i]
        data = send(ip, COMMANDS[i])
        time.sleep(1)
        data = send(ip, COMMANDSN[i])


def send(ip, message):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(0.5)
        s.connect((ip, TCP_PORT))
        s.send(bytes(str(message), "utf8"))
        data = s.recv(BUFFER_SIZE)
        s.close()
        return data
    except Exception as e:
        print("exception: ", e)
        return ""

text = [""] * 7

def live_sensors(i):
    global text
    while 1:
        ip = ips[i]
        data = send(ip, COMMANDSN[i])
        js = json.loads(data)
        try:
            js = js["sensors"]
            text[int(i)] = str(js) + "\n"
        except KeyError as e:
            print(i, ip, data, e)

        time.sleep(0.01)


if __name__ == "__main__":
    routine()
    for i in ips:
        _thread.start_new_thread( live_sensors, (i, ) )

    while 1:
        time.sleep(0.1)
        print(text)

