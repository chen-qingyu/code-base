import socket
import os

HOST = "127.0.0.1"
PORT = 9999
BUFFER_SIZE = 1024

FILE_PATH = "./serverFile.txt"
SPLIT = ": "


def find_data(key: str) -> str:
    value = "Not found"
    with open(FILE_PATH, "r") as fo:
        for line in fo.readlines():
            if line.split(SPLIT)[0] == key:
                # Find value and remove the '\n' character
                value = line.split(SPLIT)[1][:-1]
    return value


def write_data(key: str, value: str) -> str:
    with open(FILE_PATH, "a") as fo:
        fo.write(key + SPLIT + value + "\n")
    return "Write data finished."


def process_cmd(cmd) -> str:
    find = "find "
    write = "write "
    ret = ""
    if cmd[:len(find)] == find:
        ret = find_data(cmd[len(find):])
    elif cmd[:len(write)] == write:
        try:
            key, value = cmd[len(write):].split(SPLIT)
            ret = write_data(key, value)
        except ValueError:
            ret = "syntax: write <key: value>, for example: write foo: bar"
    return ret


def main():
    if not os.path.exists(FILE_PATH):
        open(FILE_PATH, "w").close()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print("Server start at IP %s, port %s\n" % (HOST, PORT))
        while True:
            conn, addr = s.accept()
            with conn:
                recv_data = conn.recv(BUFFER_SIZE)
                if recv_data.decode() == "shutdown":
                    print("Server shutdown.")
                    conn.sendall("Server shutdown.".encode())
                    break
                print("From IP %s, port %s: %s" %
                      (addr[0].strip("'"), addr[1], recv_data.decode()))
                print()
                result = process_cmd(recv_data.decode())
                if result != "":
                    conn.sendall(result.encode())
                else:
                    conn.sendall("Server received.".encode())


if __name__ == '__main__':
    main()
