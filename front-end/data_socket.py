import _thread as thread
from time import sleep

bind_ip = '127.0.0.1'
bind_port = 9001

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((bind_ip, bind_port))
server.listen(5)  # max backlog of connections

"""
Type:
1 = Change Check
2 = Give Actuator Values
3 = Receive All
"""
def data_socket_routine():
    while 1:

        sleep(0.5) # sleep 1 second


def start_data_socket_thread():
    thread.start_new_thread(data_socket_routine, ())

