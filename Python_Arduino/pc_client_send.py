import socket

#ESPのIPアドレス
host = "192.168.1.13"
port = 9999

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect((host, port))

msg = "Nice to meet you! from PC"
sock.sendall(msg.encode('ascii'))

sock.close()