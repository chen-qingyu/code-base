# FileName: auto_init.py
# Brief: Python3 script for automating initialize the system environment.
# Author: Qing Yu
# CreateDate: 2023.09.27

import os
import platform

import colorama
import requests
import tqdm

colorama.init(autoreset=True)

COLOR_START = colorama.Fore.BLUE + colorama.Style.BRIGHT
COLOR_INFO = colorama.Fore.CYAN + colorama.Style.BRIGHT
COLOR_FINISH = colorama.Fore.GREEN + colorama.Style.BRIGHT
COLOR_ERROR = colorama.Fore.RED + colorama.Style.BRIGHT


SOFTWARES = (
    {'name': 'Qt',
     'auto_download': True,
     'auto_install': True,
     'url': 'https://mirror.nju.edu.cn/qt/official_releases/online_installers/qt-unified-windows-x64-online.exe',
     'params': '--mirror https://mirror.nju.edu.cn/qt'},

    {'name': 'Sublime Text',
     'auto_download': False,
     'auto_install': False,
     'url': '',
     'params': ''},
)

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
    for i, software in zip(range(len(SOFTWARES)), SOFTWARES):
        print(COLOR_START + f"({i + 1}/{len(SOFTWARES)}) Start download/install {software['name']}...")

        if software['auto_download']:
            download(software)
            if software['auto_install']:
                install(software)
            else:
                input(COLOR_INFO + f"Please install {software['name']} manually.")
        else:
            input(COLOR_INFO + f"Please download and install {software['name']} manually.")

        print(COLOR_FINISH + f"Finish download/install {software['name']}.\n")


def download(software: dict):
    print(COLOR_INFO + f"Downloading {software['name']}...")
    file_name = software['url'].split('/')[-1]
    response = requests.get(software['url'], stream=True)
    length = int(response.headers.get('content-length', 0))
    with open(DOWNLOADS + file_name, 'wb') as fo, tqdm.tqdm(
            desc=file_name, total=length, unit='iB', unit_scale=True, unit_divisor=1024) as bar:
        for data in response.iter_content(chunk_size=1024):
            size = fo.write(data)
            bar.update(size)
    print(COLOR_INFO + f"Downloaded {software['name']}.")


def install(software: dict):
    print(COLOR_INFO + f"Installing {software['name']}...")
    file_name = software['url'].split('/')[-1]
    os.system('PowerShell ' + DOWNLOADS + file_name + ' ' + software['params'])
    print(COLOR_INFO + f"Installed {software['name']}.")


if __name__ == '__main__':
    main()
