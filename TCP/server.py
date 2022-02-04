import socket

HOST = "127.0.0.1"
PORT = 9999
BUFFER_SIZE = 1024

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print("Server start at IP %s, port %s\n" % (HOST, PORT))
    while True:
        conn, addr = s.accept()
        with conn:
            recv_data = conn.recv(BUFFER_SIZE)
            if (recv_data.decode() == "shutdown"):
                print("Server shutdown.")
                conn.sendall("Server shutdown.".encode())
                break
            print("From IP %s, port %s: %s" % (addr[0].strip("'"), addr[1], recv_data.decode()))
            print()
            conn.sendall("Server received.".encode())
