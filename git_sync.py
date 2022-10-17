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

# remote repository address: "host branch"
GITHUB = "github master"
GITEE = "gitee master"

# (path, remote, clean)
# path: string, the path of the local repository.
# remote: tuple, remote repositories address.
# clean: bool, True if use "killer.bat" to clean up temporary files, and then clean up empty directories.
repositories = [
    ("F:/C/C Primer Plus", (GITEE,), True),
    ("F:/C/C Programs", (GITEE,), True),
    ("F:/Java", (GITEE,), False),
    ("F:/OSTEP", (GITEE, GITHUB), False),
    ("F:/Projects/BadApple", (GITEE,), True),
    ("F:/Projects/Data Structure and Algorithm", (GITEE, GITHUB), False),
    ("F:/Projects/HelloWorld", (GITEE,), False),
    ("F:/Projects/LinearAlgebra", (GITEE,), False),
    ("F:/Projects/Love Miao", (GITEE,), False),
    ("F:/Python/Python Programs", (GITEE,), False),
    ("F:/Racket/HtDP", (GITEE,), False),
    ("F:/STM32/CODE", (GITEE,), True),
    ("F:/TeX", (GITEE,), True)
]


def clean(path: str):
    # use "killer.bat" to clean up temporary files, and then clean up empty directories.
    os.chdir(path)
    os.system("killer.bat")
    for path, dirs, files in os.walk(path):
        # Ignore git directory
        if path[-4:] == ".git":
            continue
        for d in dirs:
            # Delete empty folders recursively
            if os.listdir(os.path.join(path, d)) == []:
                os.removedirs(os.path.join(path, d))
                print(colorama.Fore.BLUE + colorama.Style.BRIGHT + os.path.join(path, d) + " deleted.")


def sync(path: str, remote: tuple[str, ...]):
    # synchronize Git remote repositories.
    os.chdir(path)
    cmd = "git add . && git commit -m \"batch update\""
    if GITEE in remote:
        cmd += f" && git push {GITEE}"
    if GITHUB in remote:
        cmd += f" && git push {GITHUB}"
    cmd += " && git status"
    os.system(cmd)


def main():
    print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "Start cleaning.")
    for repo in repositories:
        if repo[2]:
            clean(repo[0])
    print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "Cleaning completed.")

    print(colorama.Fore.BLUE + colorama.Style.BRIGHT + "Start synchronize.")
    for i in range(len(repositories)):
        print(colorama.Fore.CYAN + colorama.Style.BRIGHT + f"({i + 1}/{len(repositories)}) Start syncing {repositories[i][0]}:")
        sync(repositories[i][0], repositories[i][1])
        print()
    print(colorama.Fore.GREEN + colorama.Style.BRIGHT + f"Synchronize completed, {len(repositories)} repositories are synchronized.")

    input()


if __name__ == '__main__':
    main()
