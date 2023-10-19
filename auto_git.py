# FileName: auto_git.py
# Brief: Python3 script for automating batch manage git repositories.
# Author: Qing Yu
# CreateDate: 2022.02.11

import os
import tomllib

import colorama

with open('auto_git.toml', 'rb') as f:
    DATA = tomllib.load(f)
    SIZE = len(DATA['repos'])

colorama.init(autoreset=True)

COLOR_START = colorama.Fore.BLUE + colorama.Style.BRIGHT
COLOR_INFO = colorama.Fore.CYAN + colorama.Style.BRIGHT
COLOR_FINISH = colorama.Fore.GREEN + colorama.Style.BRIGHT
COLOR_ERROR = colorama.Fore.RED + colorama.Style.BRIGHT


def main():
    print(COLOR_INFO + "Welcome to the automatic git management program!")
    print()
    print("status: check repositories status.")
    print("clone:  clone remote repositories to local repositories.")
    print("push:   push local repositories to remote repositories.")
    print("pull:   pull remote repositories to local repositories.")
    print("clean:  clean up redundant files and directories.")
    print("remote: show a list of existing remote repositories.")
    print("gc:     optimize the local repositories.")
    print()
    print("exit:   exit this program.")
    print()

    while True:
        x = input("\nYour choice [status(default)/clone/push/pull/clean/remote/gc/exit]: ").strip().lower()
        if x == 'status' or x == '':
            status()
        elif x == 'clone':
            clone()
        elif x == 'push':
            push()
        elif x == 'pull':
            pull()
        elif x == 'clean':
            clean()
        elif x == 'remote':
            remote()
        elif x == 'gc':
            gc()
        elif x == 'exit':
            break
        else:
            print(COLOR_ERROR + "Invalid option: " + x)

    print("Bye!")


def exist_path(path, idx) -> bool:
    if not os.path.exists(path):
        print(COLOR_ERROR + f"({idx + 1}/{SIZE}) {path} not exists.\n")
        return False
    return True


def status():
    print(COLOR_START + "Start status.\n")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if not exist_path(repo['local'], i):
            continue
        os.chdir(repo['local'])
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Checking {repo['local']}:")
        os.system('git status')
        print()

    print(COLOR_FINISH + "Finish status.")


def clone():
    print(COLOR_START + "Start clone.\n")

    for i, repo in zip(range(SIZE), DATA['repos']):
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Cloning {repo['local']}:")
        if not os.path.exists(repo['local']):
            path, name = '/'.join(repo['local'].split('/')[:-1]), repo['local'].split('/')[-1]
            if not os.path.exists(path):
                os.mkdir(path)
            os.chdir(path)
            os.system(f'git clone {repo['remote'][repo['upstream']]} "{name}"')
            os.chdir(name)
            os.system(f'git remote rename origin {repo['upstream']}')
            print()
        else:
            print(COLOR_INFO + f"{repo['local']} already exists.\n")

    print(COLOR_FINISH + "Finish clone.")


def push():
    print(COLOR_START + "Start push.\n")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if not exist_path(repo['local'], i):
            continue
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Pushing {repo['local']}:")
        os.chdir(repo['local'])
        for host, url in repo['remote'].items():
            print(COLOR_INFO + f"to {host}:")
            os.system(f'git push {url}')
        print()

    print(COLOR_FINISH + "Finish push.")


def pull():
    print(COLOR_START + "Start pull.\n")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if not exist_path(repo['local'], i):
            continue
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Pulling {repo['local']}:")
        os.chdir(repo['local'])
        os.system(f'git pull {repo['remote'][repo['upstream']]}')

    print(COLOR_FINISH + "Finish pull.")


def clean():
    print(COLOR_START + "Start clean.\n")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if not exist_path(repo['local'], i):
            continue
        if repo['clean']:
            os.chdir(repo['local'])
            print(COLOR_INFO + f"({i + 1}/{SIZE}) Cleaning {repo['local']}:")
            # use ".gitignore" as pattern to clean up redundant files and directories recursively.
            os.system('git clean -d -f -X')
            print()

    print(COLOR_FINISH + "Finish clean.")


def remote():
    print(COLOR_START + "Start remote.\n")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if not exist_path(repo['local'], i):
            continue
        os.chdir(repo['local'])
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Showing {repo['local']}:")
        os.system('git remote --verbose')
        print()

    print(COLOR_FINISH + "Finish remote.")


def gc():
    print(COLOR_START + "Start gc.\n")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if not exist_path(repo['local'], i):
            continue
        os.chdir(repo['local'])
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Optimizing {repo['local']}:")
        os.system('git gc --aggressive')
        print()

    print(COLOR_FINISH + "Finish gc.")


if __name__ == '__main__':
    main()
