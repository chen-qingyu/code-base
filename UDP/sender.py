import socket

HOST = '127.0.0.1'
PORT = 9999

i = 1
while True:
    send_data = input("#%d: " % i)
    i += 1
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.sendto(send_data.encode(), (HOST, PORT))
    if send_data == "exit":
        break
