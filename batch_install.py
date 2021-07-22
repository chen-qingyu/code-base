import os

libs = {
    "PyInstaller", "pygame", "numba", "numpy",
    "scipy", "matplotlib", "wordcloud", "jieba",
    "imageio", "requests", "beautifulsoup4", "scrapy",
    "aiohttp", "jinja2", "aiomysql", "opencv-python",
    "django", "pyautogui", "youtube-dl"
}

os.system("python -m pip install --upgrade pip setuptools wheel -i https://pypi.doubanio.com/simple")
print("=" * 30)

for lib in libs:
    print("Now install/upgrade " + lib)
    os.system("pip install --upgrade " + lib + " -i https://pypi.doubanio.com/simple")
    print("=" * 30)

print("共安装/升级{}个库:".format(len(libs)), libs)
input()
