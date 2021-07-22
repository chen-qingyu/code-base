import socket

HOST = '127.0.0.1'
PORT = 9999

i = 1
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print('Server start: %s:%s' % (HOST, PORT))
    while True:
        conn, addr = s.accept()
        with conn:
            recv_data = conn.recv(1024)
            if (recv_data.decode() == "exit"):
                print('Bye!')
                conn.send('Bye!'.encode())
                break
            print('#%d @%s: %s\n' % (i, addr, recv_data.decode()))
            conn.send(('#%d Got it!' % i).encode())
            i += 1
