import socket

host = "192.168.1.7"
port = 4545

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((host, port))
sock.listen(1)

cs, cadder = sock.accept()

while True:
    msg = cs.recv(1024)
    print(msg.decode('ascii'))
    break

sock.close()