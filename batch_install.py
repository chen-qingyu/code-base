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

    "colorama"
]

if __name__ == '__main__':
    for lib in libs:
        print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "Now install/upgrade " + lib)
        os.system("python -m pip install --upgrade \
        -i https://pypi.tuna.tsinghua.edu.cn/simple/ " + lib)
        print()

    print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "A total of {} libraries have been installed/upgraded:".format(len(libs)), libs)
    input()
