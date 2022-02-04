import socket

HOST = "127.0.0.1"
PORT = 9999
BUFFER_SIZE = 1024

print("Welcome to the TCP simulation applet.")
print("cmd:")
print("  exit - Exit the client.")
print("  shutdown - Shut down the server.")
print("To IP %s, port %s" % (HOST, PORT))
print()
while True:
    send_data = input("cmd: ")
    if send_data.strip() == "":
        continue
    if send_data == "exit":
        break
    with socket.socket() as s:
        try:
            s.connect((HOST, PORT))
        except socket.error:
            print("Connection failed.\n")
            continue
        s.sendall(send_data.encode())
        recv_data = s.recv(BUFFER_SIZE)
        print(recv_data.decode(), "\n")
print("Bye!")