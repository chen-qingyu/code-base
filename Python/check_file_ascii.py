import sys
import os
import colorama

colorama.init(autoreset=True)
COLOR_START = colorama.Fore.BLUE + colorama.Style.BRIGHT
COLOR_INFO = colorama.Fore.CYAN + colorama.Style.BRIGHT
COLOR_FINISH = colorama.Fore.GREEN + colorama.Style.BRIGHT
COLOR_ERROR = colorama.Fore.RED + colorama.Style.BRIGHT


def check_file_ascii(file):
    """
    Check characters in the file and output lines containing non ASCII characters.
    """
    non_ascii_lines = []

    try:
        with open(file, 'r', encoding='utf-8') as fo:
            for line_number, line in enumerate(fo, start=1):
                if not line.isascii():
                    non_ascii_lines.append((line_number, line.strip()))
    except FileNotFoundError:
        print(COLOR_ERROR+f"File {file} not found.")
        return
    except Exception as e:
        print(COLOR_ERROR+f"Error while reading {file}: {e}.")
        return

    if non_ascii_lines:
        print(COLOR_ERROR+f"File {file} contains non-ASCII lines:")
        for line_number, line in non_ascii_lines:
            print(COLOR_INFO+f"Line {line_number}:")
            print(line)
    else:
        print(COLOR_FINISH+f"File {file} all ASCII.")


def check_folder_ascii(folder):
    """
    Traverse all files in the specified directory and check each file.
    """
    if not os.path.isdir(folder):
        print(COLOR_ERROR+f"Invalid path: {folder}.")
        return

    for root, dirs, files in os.walk(folder):
        for file in files:
            path = os.path.join(root, file)
            if '.git' in path:  # ignore .git/
                continue
            print(COLOR_START+f"Checking {path}:")
            check_file_ascii(path)


if __name__ == '__main__':
    if len(sys.argv) == 2:
        check_folder_ascii(sys.argv[1])
    else:
        print("useage: check_file_ascii.py <folder_path>")
