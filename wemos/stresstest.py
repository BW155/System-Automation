import time
import socket
import binascii
import json
import math


TCP_IP = '192.168.2.2'
TCP_PORT = 8080
BUFFER_SIZE = 1024


todo = 10000
tries = todo
fails = 0
state = 0

times = []
last_error = ""


def millis():
    millis = int(round(time.time() * 1000))
    return millis


def routine():
    global fails, state, tries, last_error
    state = 1 if state == 0 else 0

    t = millis()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    MESSAGE = str({"name":"Bed","actuators":[{"name":"led","value":int(state)}]}).encode('utf-8')
    s.connect((TCP_IP, TCP_PORT))
    s.send(MESSAGE)
    data = s.recv(BUFFER_SIZE)
    s.close()

    times.append(millis() - t)

    js = json.loads(data)
    if js["error"] != "":
        last_error = js["error"]
        fails += 1

    tries -= 1


begin = millis()

while tries > 0:
    routine()
    print('tries left: {0}, errors: {1}, last_error: {2}'.format(tries, fails, last_error), end=("\r" if tries > 0 else "\n"))


print("%d errors and %d success" % (fails, len(times) - fails))
print("Average time millis: ", sum(times) / len(times))
print("Total in seconds: ", (millis() - begin) / 1000)
print("fastest time millis: ", min(times))

