import socket

HOST = '127.0.0.1'
PORT = 9999

i = 1
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    s.bind((HOST, PORT))
    print('Server start: %s:%s' % (HOST, PORT))
    while True:
        recv_data, addr = s.recvfrom(1024)
        if (recv_data.decode() == "exit"):
            print('Bye!')
            break
        print('#%d @%s: %s\n' % (i, addr, recv_data.decode()))
        i += 1
