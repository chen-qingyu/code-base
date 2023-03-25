import socket
import sqlite3

HOST = "127.0.0.1"
PORT = 9999
BUFFER_SIZE = 1024

DATABASE_PATH = "./tcp_data.db"

sql_conn = sqlite3.connect(DATABASE_PATH)
sql_cur = sql_conn.cursor()
# create a data table if it doesn't exist.
sql_cur.execute("SELECT * FROM sqlite_master WHERE type = 'table' AND name = 'data';")
if sql_cur.fetchone() is None:
    sql_cur.execute("CREATE TABLE data (key text PRIMARY KEY, value text NOT NULL);")
    sql_conn.commit()


def find_data(key: str) -> str:
    sql_cur.execute("SELECT value FROM data WHERE key=?;", (key,))
    value = sql_cur.fetchone()
    return value[0] if value is not None else ("Not found: " + key)


def write_data(key: str, value: str) -> str:
    try:
        sql_cur.execute("INSERT INTO data VALUES (?, ?);", (key, value))
        sql_conn.commit()
        return "Write data finished"
    except sqlite3.IntegrityError:
        return "Write data failure: key should be unique"


def update_data(key: str, value: str) -> str:
    sql_cur.execute("UPDATE data SET value=? WHERE key=?;", (value, key))
    sql_conn.commit()
    if sql_cur.rowcount == 1:
        return "Update data finished"
    else:
        return "Update data failure: key does not exist"


def delete_data(key: str) -> str:
    sql_cur.execute("DELETE FROM data WHERE key=?;", (key,))
    sql_conn.commit()
    if sql_cur.rowcount == 1:
        return "Delete data finished"
    else:
        return "Delete data failure: key does not exist"


def process_cmd(cmd: str) -> str:
    match cmd.split():
        case ["find", key]:
            return find_data(key)
        case ["write", key, value]:
            return write_data(key[:-1], value)
        case ["update", key, value]:
            return update_data(key[:-1], value)
        case ["delete", key]:
            return delete_data(key)
        case _:
            return "Server received."


def main():
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
                print("From IP %s, port %s: %s\n" % (addr[0].strip("'"), addr[1], recv_data.decode()))
                conn.sendall(process_cmd(recv_data.decode()).encode())


if __name__ == '__main__':
    main()
