# FileName: batch_git.py
# Brief: Python3 script for automating batch manage git repositories.
# Author: Qing Yu
# CreateDate: 2022.02.11

import os
import colorama

colorama.init(autoreset=True)

COLOR_START = colorama.Fore.BLUE + colorama.Style.BRIGHT
COLOR_INFO = colorama.Fore.CYAN + colorama.Style.BRIGHT
COLOR_FINISH = colorama.Fore.GREEN + colorama.Style.BRIGHT
COLOR_ERROR = colorama.Fore.RED + colorama.Style.BRIGHT

# remote repository address: "host branch"
GITHUB = "github master"
GITEE = "gitee master"

# REPOS: ((root, addresses, clean), ...)
# root: string, the root path of the local repository.
# addresses: (string, ...), remote repository addresses.
# clean: bool, True if use "root/.gitignore" as pattern to clean up redundant files and directories.
REPOS = (
    ("F:/C/C Programs", (GITEE, GITHUB), True),
    ("F:/Python/Python Programs", (GITEE, GITHUB), False),
    ("F:/Java/Java Programs", (GITEE, GITHUB), False),
    ("F:/C/C Primer Plus", (GITEE, GITHUB), True),
    ("F:/Java/StuScore", (GITEE, GITHUB), False),
    ("F:/OSTEP", (GITEE, GITHUB), False),
    ("F:/Projects/BadApple", (GITEE, GITHUB), True),
    ("F:/Projects/HelloWorld", (GITEE, GITHUB), False),
    ("F:/Projects/LinearAlgebra", (GITEE, GITHUB), False),
    ("F:/Projects/Love Miao", (GITEE, GITHUB), False),
    ("F:/Racket/HtDP", (GITEE, GITHUB), False),
    ("F:/STM32/STM32 Programs", (GITEE, GITHUB), True),
    ("F:/TeX", (GITEE, GITHUB), True),
    ("F:/Projects/TestTime", (GITEE, GITHUB), True),
    ("F:/Projects/MDS", (GITEE, GITHUB), False),
    ("F:/Projects/MDSPP", (GITEE, GITHUB), False)
)


def main():
    print("Welcome to the automatic git management program!")
    print()
    print("S: status -- check repositories status.")
    print("P: push -- push local repositories to remote repositories.")
    print("C: clean -- clean up redundant files and directories.")
    print("R: remote -- show a list of existing remote repositories.")
    print("G: gc -- optimize the local repositories.")
    print()
    print("Q: quit -- quit this program.")
    print()

    while True:
        x = input("\nYour choice [S(default)/P/C/R/G/Q]: ").strip()
        if x in "sS":  # "" in "sS" is True
            status()
        elif x in "pP":
            push()
        elif x in "cC":
            clean()
        elif x in "rR":
            remote()
        elif x in "gG":
            gc()
        elif x in "qQ":
            break
        else:
            print(COLOR_ERROR + "Invalid option: " + x)

    print("Bye!")


def status():
    print(COLOR_START + "Start status.")

    for root, _, _ in REPOS:
        os.chdir(root)
        print(COLOR_INFO + f"Checking {root}:")
        os.system("git status")
        print()

    print(COLOR_FINISH + "Finish status.")


def push():
    print(COLOR_START + "Start push.")

    for root, addresses, _ in REPOS:
        print(COLOR_INFO + f"Pushing {root}:")
        os.chdir(root)
        for address in addresses:
            print(COLOR_INFO + f"to {address}:")
            os.system(f"git push {address}")
        print()

    print(COLOR_FINISH + "Finish push.")


def clean():
    print(COLOR_START + "Start clean.")

    for root, _, clean in REPOS:
        if clean:
            os.chdir(root)
            print(COLOR_INFO + f"Cleaning {root}:")
            # use ".gitignore" as pattern to clean up redundant files and directories recursively.
            os.system("git clean -d -f -X")
            print()

    print(COLOR_FINISH + "Finish clean.")


def remote():
    print(COLOR_START + "Start remote.")

    for root, _, _ in REPOS:
        os.chdir(root)
        print(COLOR_INFO + f"Showing {root}:")
        os.system("git remote --verbose")
        print()

    print(COLOR_FINISH + "Finish remote.")


def gc():
    print(COLOR_START + "Start gc.")

    for root, _, _ in REPOS:
        os.chdir(root)
        print(COLOR_INFO + f"Optimizing {root}:")
        os.system("git gc --aggressive")
        print()

    print(COLOR_FINISH + "Finish gc.")


if __name__ == '__main__':
    main()
