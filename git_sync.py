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

GITHUB = 1
GITEE = 2

repositories = [("F:/C/C Primer Plus", (GITEE,)),
                ("F:/C/C Programs", (GITEE,)),
                ("F:/Java", (GITEE,)),
                ("F:/OSTEP", (GITEE, GITHUB)),
                ("F:/Projects/BadApple", (GITEE,)),
                ("F:/Projects/Data Structure and Algorithm", (GITEE, GITHUB)),
                ("F:/Projects/HelloWorld", (GITEE,)),
                ("F:/Projects/LinearAlgebra", (GITEE,)),
                ("F:/Projects/Love Miao", (GITEE,)),
                ("F:/Python/Python Programs", (GITEE,)),
                ("F:/Racket/HtDP", (GITEE,)),
                ("F:/STM32/CODE", (GITEE,)),
                ("F:/TeX", (GITEE,))]

# "killer.bat"
killersPaths = ["F:/C",
                "F:/Projects/BadApple",
                "F:/STM32/CODE",
                "F:/Projects/Data Structure and Algorithm/C",
                "F:/TeX"]

clearEmptyDirsPaths = ["F:/Projects/BadApple",
                       "F:/STM32/CODE"]


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
    os.chdir(repositories[index][0])
    print(colorama.Fore.CYAN + colorama.Style.BRIGHT + f"({index + 1}/{len(repositories)}) Start syncing {repositories[index][0]}:")
    if GITEE in repositories[index][1]:
        cmd += " && git push gitee master"
    if GITHUB in repositories[index][1]:
        cmd += " && git push github master"
    os.system(cmd)
    print()


def main():
    print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "Start deleting unnecessary files.")
    for path in killersPaths:
        delUnnecessaryFiles(path)
    print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "The unnecessary files are deleted.")

    print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "Start deleting empty folders.")
    for path in clearEmptyDirsPaths:
        delEmptyDirs(path)
    print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "The empty folders are deleted.")

    print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "Start synchronize.")
    for index in range(len(repositories)):
        gitSync(index, "git add . && git commit -m \"batch update\"")
    print(colorama.Fore.GREEN + colorama.Style.BRIGHT + f"Synchronize completed, {len(repositories)} repositories are synchronized.")

    input()


if __name__ == '__main__':
    main()
