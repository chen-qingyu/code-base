import os

libs = [
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

    # TODO
    # "tensorflow",
]


accelerate = " -i https://pypi.tuna.tsinghua.edu.cn/simple/"
os.system("python -m pip install --upgrade pip setuptools wheel")
print("=" * 40)

for lib in libs:
    print("Now install/upgrade " + lib)
    os.system("python -m pip install --upgrade " + lib)
    print("=" * 40)

print("共安装/升级{}个库:".format(len(libs)), libs)
input("按任意键关闭窗口")
