import sys
import os


def add_endline_if_missing(file):
    with open(file, 'rb') as f:
        f.seek(0, os.SEEK_END)
        size = f.tell()
        if size == 0:
            return False
        f.seek(-1, os.SEEK_END)
        last_byte = f.read(1)
        if last_byte == b'\n':
            return False
    with open(file, 'ab') as f:
        f.write(b'\n')
    return True


def process_directory(directory):
    if not os.path.isdir(directory):
        print(f"Error: {directory} is not a valid directory.")
        return
    for root, _, files in os.walk(directory):
        for file in files:
            file = os.path.join(root, file)
            if add_endline_if_missing(file):
                print(f"Completed end newline: {file}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python add_endline.py <directory>")
    else:
        process_directory(sys.argv[1])
