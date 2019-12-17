import _thread as thread
from time import sleep


def data_socket_routine():
    while 1:
        sleep(1) # sleep 1 second


def start_data_socket_thread():
    thread.start_new_thread(data_socket_routine, ())

