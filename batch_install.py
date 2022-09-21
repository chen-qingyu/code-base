import os
import colorama

colorama.init(autoreset=True)

libs = [
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
]

if __name__ == '__main__':
    for i in range(len(libs)):
        print(colorama.Fore.BLUE + colorama.Style.BRIGHT + f"({i + 1}/{len(libs)}) Now install/upgrade {libs[i]}")
        os.system("python -m pip install --upgrade -i https://pypi.tuna.tsinghua.edu.cn/simple/ " + libs[i])
        print()

    print(colorama.Fore.GREEN + colorama.Style.BRIGHT
          + f"A total of {len(libs)} libraries have been installed/upgraded: "
          + str(libs).replace("'", ""))
    input()
