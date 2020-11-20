import socket

host = "192.168.1.13"
port = 9999

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect((host, port))

msg = "get data"

sock.sendall(msg.encode('ascii'))

data = sock.recv(1024)
print(data.decode('ascii'))

sock.close()
