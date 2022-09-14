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

GitPaths = ["F:/C/C Primer Plus",
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
KillersPaths = ["F:/C",
                "F:/Projects/BadApple",
                "F:/STM32/CODE",
                "F:/Projects/Data Structure and Algorithm/C",
                "F:/TeX"]

ClearEmptyDirsPaths = ["F:/Projects/BadApple",
                       "F:/STM32/CODE"]

SyncCmd = "git add . && git commit -m \"update\" && git push && git status"


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


def gitSync(index, cmd):
    os.chdir(GitPaths[index])
    print(colorama.Fore.CYAN + colorama.Style.BRIGHT + f"({index + 1}/{len(GitPaths)}) Start syncing {GitPaths[index]}:")
    os.system(cmd)
    print()


def main():
    print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "Start deleting unnecessary files.")
    for path in KillersPaths:
        delUnnecessaryFiles(path)
    print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "The unnecessary files are deleted.")

    print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "Start deleting empty folders.")
    for path in ClearEmptyDirsPaths:
        delEmptyDirs(path)
    print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "The empty folders are deleted.")

    print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "Start synchronize.")
    for i in range(len(GitPaths)):
        gitSync(i, SyncCmd)
    print(colorama.Fore.GREEN + colorama.Style.BRIGHT + f"Synchronize completed, {len(GitPaths)} repositories are synchronized.")

    input()


if __name__ == '__main__':
    main()
