# FileName: auto_init.py
# Brief: Python3 script for automating initialize the system environment.
# Author: Qing Yu
# CreateDate: 2023.09.27

import os
import platform
import webbrowser
import importlib
import tomllib

with open('auto_init.toml', 'rb') as f:
    data = tomllib.load(f)

# install/upgrade libraries and clean cache
os.system(f'python -m pip install --upgrade --index-url https://pypi.tuna.tsinghua.edu.cn/simple {' '.join(data['libraries'])}')
os.system("python -m pip cache purge")

# dynamically loading third-party libraries
colorama = importlib.import_module('colorama')
requests = importlib.import_module('requests')
tqdm = importlib.import_module('tqdm')

colorama.init(autoreset=True)

COLOR_START = colorama.Fore.BLUE + colorama.Style.BRIGHT
COLOR_INFO = colorama.Fore.CYAN + colorama.Style.BRIGHT
COLOR_FINISH = colorama.Fore.GREEN + colorama.Style.BRIGHT
COLOR_ERROR = colorama.Fore.RED + colorama.Style.BRIGHT

DOWNLOADS = './Downloads/'


def main():
    init()
    process()


def init():
    print(COLOR_START + "Start init.")

    if platform.system() != 'Windows':
        print(COLOR_ERROR + "This script currently only supports the Windows platform.\n")
        exit(-1)

    if not os.path.exists(DOWNLOADS):
        print(COLOR_INFO + f"Creates downloads folder: {DOWNLOADS}")
        os.mkdir(DOWNLOADS)

    print(COLOR_FINISH + "Finish init.\n")


def process():
    for i, software in zip(range(len(data['softwares'])), data['softwares']):
        print(COLOR_START + f"({i + 1}/{len(data['softwares'])}) Start download/install {software['name']}...")

        if software['method'] == 'use_winget':
            os.system('winget install ' + software['name'])
        elif software['method'] == 'auto_download_install':
            download(software)
            install(software)
        elif software['method'] == 'auto_download':
            download(software)
            input(COLOR_INFO + f"Please install {software['name']} manually.")
        elif software['method'] == 'manual':
            webbrowser.open(software['download_link'])
            input(COLOR_INFO + f"Please download and install {software['name']} manually.")
        else:
            print(COLOR_ERROR + "ERROR: Wrong method.")

        print(COLOR_FINISH + f"Finish download/install {software['name']}.\n")


def download(software: dict):
    print(COLOR_INFO + f"Downloading {software['name']}...")
    file_name = software['download_url'].split('/')[-1]
    response = requests.get(software['download_url'], stream=True)
    length = int(response.headers.get('content-length', 0))
    with open(DOWNLOADS + file_name, 'wb') as fo, tqdm.tqdm(
            desc=file_name, total=length, unit='iB', unit_scale=True, unit_divisor=1024) as bar:
        for data in response.iter_content(chunk_size=1024):
            size = fo.write(data)
            bar.update(size)
    print(COLOR_INFO + f"Downloaded {software['name']}.")


def install(software: dict):
    print(COLOR_INFO + f"Installing {software['name']}...")
    file_name = software['download_url'].split('/')[-1]
    os.system('PowerShell ' + DOWNLOADS + file_name + ' ' + software['install_args'])
    print(COLOR_INFO + f"Installed {software['name']}.")


if __name__ == '__main__':
    main()
