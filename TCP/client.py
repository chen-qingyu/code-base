import socket

HOST = "127.0.0.1"
PORT = 9999
BUFFER_SIZE = 1024


def main():
    print("Welcome to the TCP simulation applet.")
    print("Commands:")
    print("  find <key> - Find the value for the given key.")
    print("  write <key: value> - Write key-value pair.")
    print("  update <key: value> - Update key-value pair.")
    print("  exit - Exit the client.")
    print("  shutdown - Shut down the server.")
    print("In addition to the above, the data sent will be received by the server without response.")
    print("To IP %s, port %s" % (HOST, PORT))
    print()
    while True:
        send_data = input(">>> ")
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


if __name__ == '__main__':
    main()
