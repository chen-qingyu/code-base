import os
from pprint import pprint


def read_import(file_name: str, s: set):
    print(file_name + ":")
    with open(file_name, 'r', encoding='utf-8') as f:
        for line in f.readlines():
            if not ('#' in line or 'import' in line):
                break
            if '#' in line:
                continue
            s.add(line[:-1].split()[1])
            print(line[:-1].split()[1])
    print()


s = set()
root = 'F:/Python'
os.chdir(root)
for root, dirs, files in os.walk(root):
    for file in files:
        if file[-3:] == '.py':
            read_import(os.path.join(root, file), s)
pprint(s)
