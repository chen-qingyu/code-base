import socket

HOST = '127.0.0.1'
PORT = 9999

i = 1
while True:
    send_data = input("#%d: " % i)
    i += 1
    with socket.socket() as s:
        s.connect((HOST, PORT))
        s.send(send_data.encode())
        recv_data = s.recv(1024)
        print('Server: %s\n' % recv_data.decode())
    if send_data == "exit":
        break
