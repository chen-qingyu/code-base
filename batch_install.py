# FileName: batch_install.py
# Brief: Python3 script for automating batch install/upgrade libraries.
# Author: Qing Yu
# CreateDate: 2020.10.04
# Functions:
#   - install libraries,
#   - upgrade libraries

import os
import colorama

colorama.init(autoreset=True)

COLOR_START = colorama.Fore.BLUE + colorama.Style.BRIGHT
COLOR_INFO = colorama.Fore.CYAN + colorama.Style.BRIGHT
COLOR_FINISH = colorama.Fore.GREEN + colorama.Style.BRIGHT

LIBS = (
    "pip",
    "setuptools",
    "wheel",

    "numpy",
    "matplotlib",
    "scipy",
    "pandas",

    "pillow",  # PIL
    "pyinstaller",
    "pygame",
    "pyautogui",
    "pyserial",  # serial

    "wordcloud",
    "jieba",

    "requests",
    "beautifulsoup4",  # bs4

    "opencv-python",  # cv2

    "tensorflow",

    "jupyter",

    "autopep8",

    "easyocr",

    "colorama",

    "pyside6",  # PySide6
    "pyqt6"  # PyQt6
)

if __name__ == '__main__':
    for i in range(len(LIBS)):
        print(COLOR_START + f"({i + 1}/{len(LIBS)}) Start install/upgrade {LIBS[i]}")
        os.system("python -m pip install --upgrade -i https://pypi.tuna.tsinghua.edu.cn/simple/ " + LIBS[i])
        print()

    print(COLOR_FINISH + f"A total of {len(LIBS)} libraries have been installed/upgraded.")
    input()
