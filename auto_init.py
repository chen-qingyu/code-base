# FileName: auto_init.py
# Brief: Python3 script for automating initialize the system environment.
# Author: Qing Yu
# CreateDate: 2023.09.27

import os
import platform
import webbrowser

import colorama
import requests
import tqdm

colorama.init(autoreset=True)

COLOR_START = colorama.Fore.BLUE + colorama.Style.BRIGHT
COLOR_INFO = colorama.Fore.CYAN + colorama.Style.BRIGHT
COLOR_FINISH = colorama.Fore.GREEN + colorama.Style.BRIGHT
COLOR_ERROR = colorama.Fore.RED + colorama.Style.BRIGHT

# software information keys
NAME = 'name'  # software name, use the full name in winget if method is USE_WINGET
METHOD = 'method'  # how to install the software
DOWNLOAD_URL = 'download url'  # if automatic download, the download address
INSTALL_ARGS = 'install args'  # if automatic install, the install arguments
DOWNLOAD_LINK = 'download link'  # if manual download and install, the download link

# METHOD: how to automatically download and install softwares
MANUAL = 0
AUTO_DOWNLOAD = 1
AUTO_DOWNLOAD_INSTALL = 2
USE_WINGET = 3

SOFTWARES = (
    {
        NAME: 'Qt',
        METHOD: AUTO_DOWNLOAD_INSTALL,
        DOWNLOAD_URL: 'https://mirror.nju.edu.cn/qt/official_releases/online_installers/qt-unified-windows-x64-online.exe',
        INSTALL_ARGS: '--mirror https://mirror.nju.edu.cn/qt',
    },

    {
        NAME: 'Sublime Text',
        METHOD: MANUAL,
        DOWNLOAD_LINK: 'https://www.sublimetext.com/download_thanks?target=win-x64',
    },

    {
        NAME: 'Bandizip',
        METHOD: MANUAL,
        DOWNLOAD_LINK: 'https://www.bandisoft.com/bandizip/dl.php?web',
    },
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
        print(COLOR_START + f"({i + 1}/{len(SOFTWARES)}) Start download/install {software[NAME]}...")

        if software[METHOD] == USE_WINGET:
            os.system('winget install ' + software[NAME])
        elif software[METHOD] == AUTO_DOWNLOAD_INSTALL:
            download(software)
            install(software)
        elif software[METHOD] == AUTO_DOWNLOAD:
            download(software)
            input(COLOR_INFO + f"Please install {software[NAME]} manually.")
        elif software[METHOD] == MANUAL:
            webbrowser.open(software[DOWNLOAD_LINK])
            input(COLOR_INFO + f"Please download and install {software[NAME]} manually.")
        else:
            print(COLOR_ERROR + "ERROR: Wrong method.")

        print(COLOR_FINISH + f"Finish download/install {software[NAME]}.\n")


def download(software: dict):
    print(COLOR_INFO + f"Downloading {software[NAME]}...")
    file_name = software[DOWNLOAD_URL].split('/')[-1]
    response = requests.get(software[DOWNLOAD_URL], stream=True)
    length = int(response.headers.get('content-length', 0))
    with open(DOWNLOADS + file_name, 'wb') as fo, tqdm.tqdm(
            desc=file_name, total=length, unit='iB', unit_scale=True, unit_divisor=1024) as bar:
        for data in response.iter_content(chunk_size=1024):
            size = fo.write(data)
            bar.update(size)
    print(COLOR_INFO + f"Downloaded {software[NAME]}.")


def install(software: dict):
    print(COLOR_INFO + f"Installing {software[NAME]}...")
    file_name = software[DOWNLOAD_URL].split('/')[-1]
    os.system('PowerShell ' + DOWNLOADS + file_name + ' ' + software[INSTALL_ARGS])
    print(COLOR_INFO + f"Installed {software[NAME]}.")


if __name__ == '__main__':
    main()
