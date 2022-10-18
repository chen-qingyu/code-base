# FileName: git_sync.py
# Brief: Python3 script for automating batch synchronization of Git remote repositories.
# Author: Qing Yu
# CreateDate: 2022.02.11
# Functions:
#   - clean up temporary files,
#   - clean up empty directories,
#   - batch synchronize Git remote repositories

import os
import colorama

colorama.init(autoreset=True)

COLOR_START = colorama.Fore.BLUE + colorama.Style.BRIGHT
COLOR_INFO = colorama.Fore.CYAN + colorama.Style.BRIGHT
COLOR_FINISH = colorama.Fore.GREEN + colorama.Style.BRIGHT

# remote repository address: "host branch"
GITHUB = "github master"
GITEE = "gitee master"

# repositories: ((path, remote, clean), ...)
# path: string, the path of the local repository.
# remote: (string, ...), remote repository address.
# clean: bool, True if use "killer.bat" to clean up temporary files, and then clean up empty directories.
REPOS = (
    ("F:/C/C Programs", (GITEE, GITHUB), True),
    ("F:/Python/Python Programs", (GITEE, GITHUB), False),
    ("F:/Java/Java Programs", (GITEE, GITHUB), False),
    ("F:/C/C Primer Plus", (GITEE, GITHUB), True),
    ("F:/Java/StuScore", (GITEE, GITHUB), False),
    ("F:/OSTEP", (GITEE, GITHUB), False),
    ("F:/Projects/BadApple", (GITEE, GITHUB), True),
    ("F:/Projects/Data Structure and Algorithm", (GITEE, GITHUB), False),
    ("F:/Projects/HelloWorld", (GITEE, GITHUB), False),
    ("F:/Projects/LinearAlgebra", (GITEE, GITHUB), False),
    ("F:/Projects/Love Miao", (GITEE, GITHUB), False),
    ("F:/Racket/HtDP", (GITEE, GITHUB), False),
    ("F:/STM32/CODE", (GITEE, GITHUB), True),
    ("F:/TeX", (GITEE, GITHUB), True)
)


def clean(path: str):
    # use "killer.bat" to clean up temporary files, and then clean up empty directories.
    os.chdir(path)
    os.system("killer.bat")
    for root, dirs, files in os.walk(path):
        for d in dirs:
            # Ignore git directory
            if ".git" in os.path.join(root, d):
                continue
            # Delete empty folders recursively
            if os.listdir(os.path.join(root, d)) == []:
                os.removedirs(os.path.join(root, d))
                print(COLOR_INFO + os.path.join(root, d) + " deleted.")


def sync(path: str, remote: tuple[str, ...]):
    # synchronize Git remote repositories.
    os.chdir(path)
    # modified, commit successfully
    if os.system("git add . && git commit -m \"batch update\"") == 0:
        for address in remote:
            print(COLOR_INFO + f"---{address}---")
            os.system(f"git push {address}")


def main():
    print(COLOR_START + "Start cleaning.")
    for repo in REPOS:
        if repo[2]:
            clean(repo[0])
    print(COLOR_FINISH + "Cleaning completed.")

    print(COLOR_START + "Start synchronize.")
    for i in range(len(REPOS)):
        print(COLOR_INFO + f"({i + 1}/{len(REPOS)}) Start syncing {REPOS[i][0]}:")
        sync(REPOS[i][0], REPOS[i][1])
        print()
    print(COLOR_FINISH + f"Synchronize completed, {len(REPOS)} repositories are synchronized.")

    input()


if __name__ == '__main__':
    main()
