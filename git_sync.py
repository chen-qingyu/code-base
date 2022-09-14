# FileName: git_sync.py
# Brief: Python3 script for automating batch synchronization of Git remote repositories
# Author: Qing Yu
# CreateDate: 2022.02.11
# Functions:
#   - delete specific suffix files,
#   - delete empty folders,
#   - batch synchronize Git remote repositories

import os
import colorama

colorama.init(autoreset=True)

gitPaths = ["F:/C/C Primer Plus",
            "F:/C/C Programs",
            "F:/Java",
            "F:/OSTEP",
            "F:/Projects/BadApple",
            "F:/Projects/Data Structure and Algorithm",
            "F:/Projects/HelloWorld",
            "F:/Projects/LinearAlgebra",
            "F:/Projects/Love Miao",
            "F:/Python/Python Programs",
            "F:/Racket/HtDP",
            "F:/STM32/CODE",
            "F:/TeX"]

# "killer.bat"
killersPaths = ["F:/C",
                "F:/Projects/BadApple",
                "F:/STM32/CODE",
                "F:/Projects/Data Structure and Algorithm/C",
                "F:/TeX"]

clearEmptyDirsPaths = ["F:/Projects/BadApple",
                       "F:/STM32/CODE"]

syncCmd = "git add . && git commit -m \"update\" && git push && git status"


def delUnnecessaryFiles(path):
    os.chdir(path)
    os.system("killer.bat")


def delEmptyDirs(root):
    os.chdir(root)
    for root, dirs, files in os.walk(root):
        # Ignore git directory
        if root[-4:] == ".git":
            continue
        for d in dirs:
            # Delete empty folders recursively
            if os.listdir(os.path.join(root, d)) == []:
                os.removedirs(os.path.join(root, d))
                print(os.path.join(root, d) + " deleted.")


def gitSync(path, cmd):
    os.chdir(path)
    print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "[Start syncing \"" + path + "\"]")
    os.system(cmd)
    print()


def main():
    pattern = ("=" * 5)

    print(pattern, "Start deleting unnecessary files", pattern)
    for path in killersPaths:
        delUnnecessaryFiles(path)
    print(pattern, "The unnecessary files are deleted", pattern)

    print(pattern, "Start deleting empty folders", pattern)
    for path in clearEmptyDirsPaths:
        delEmptyDirs(path)
    print(pattern, "The empty folders are deleted", pattern)

    print(pattern, "Start synchronize", pattern)
    for path in gitPaths:
        gitSync(path, syncCmd)
    print(pattern, "Synchronize completed, {} repositories are synchronized".format(len(gitPaths)), pattern)

    input()


if __name__ == '__main__':
    main()
