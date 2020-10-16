import socket
import time
HOST = "192.168.10.102"
PORT = 30002
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((HOST,PORT))