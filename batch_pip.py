# FileName: batch_pip.py
# Brief: Python3 script for automating batch install/upgrade libraries.
# Author: Qing Yu
# CreateDate: 2020.10.04

import os
import importlib

LIBS = (
    # "numpy",  # the latest version conflicts with tensorflow
    "scipy",
    "pandas",

    "matplotlib",
    "pillow",  # PIL

    "pyinstaller",
    "pygame",
    "pyautogui",
    "pyserial",  # serial

    "wordcloud",
    "jieba",

    "requests",
    "beautifulsoup4",  # bs4

    "opencv-python",  # cv2, name conflict with easyocr's dep: opencv-python-headless

    "tensorflow",

    "jupyter",

    "autopep8",

    "colorama",

    "pyside6",  # PySide6
    "pyqt6",  # PyQt6

    "graph-tools",

    "objprint",
    "viztracer",

    "django",
    "djlint",
)


def main():
    init()
    process()


def init():
    print("Start init.\n")

    print("Configuring mirror source.")
    os.system("python -m pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple")
    print("Configured mirror source.\n")

    print("Upgrading pip tools.")
    os.system("python -m pip install --upgrade pip setuptools wheel")
    print("Upgraded pip tools.\n")

    print("Loading colorama.")
    if importlib.util.find_spec("colorama") is None:
        os.system("python -m pip install colorama")
    colorama = importlib.import_module("colorama")
    colorama.init(autoreset=True)
    global COLOR_START, COLOR_INFO, COLOR_FINISH, COLOR_ERROR
    COLOR_START = colorama.Fore.BLUE + colorama.Style.BRIGHT
    COLOR_INFO = colorama.Fore.CYAN + colorama.Style.BRIGHT
    COLOR_FINISH = colorama.Fore.GREEN + colorama.Style.BRIGHT
    COLOR_ERROR = colorama.Fore.RED + colorama.Style.BRIGHT
    print(COLOR_INFO + "Loaded colorama.\n")

    print(COLOR_FINISH + "Finish init.\n")


def process():
    print(COLOR_START + "Start install/upgrade libraries.\n")

    for i in range(len(LIBS)):
        print(COLOR_INFO + f"({i + 1}/{len(LIBS)}) installing/upgrading {LIBS[i]}")
        os.system("python -m pip install --upgrade " + LIBS[i])
        print()

    print(COLOR_FINISH + f"A total of {len(LIBS)} libraries have been installed/upgraded.")


if __name__ == '__main__':
    main()
