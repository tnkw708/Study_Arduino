import socket

host = "192.168.1.7"
port = 1919

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((host, port))
sock.listen(1)

cs, caddr = sock.accept()

msg = "Hello! from PC"

while True:
    cs.sendall(msg.encode('ascii'))
    break

sock.close()