# FileName: auto_git.py
# Brief: Python3 script for automating batch manage git repositories.
# Author: Qing Yu
# CreateDate: 2022.02.11

import os
import tomllib
import sys
import argparse

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
    parser = argparse.ArgumentParser(prog='auto_git', description="Python3 script for automating batch manage git repositories.")
    parser.add_argument("action", type=str, help="git action", choices=['status', 'clone', 'push', 'pull', 'clean', 'remote', 'gc'])
    parser.add_argument("name", type=str, help="Abbreviation of repository name", nargs='?', default='')

    # interactive mode
    if len(sys.argv) == 1:
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
            choice = input("\nYour choice (default = status): ").strip().lower().split()
            if choice == []:
                process('status', '')
            elif choice == ['exit']:
                print("Bye!")
                break
            else:
                args = parser.parse_args(choice)
                process(args.action, args.name)
    # command mode
    else:
        args = parser.parse_args()
        process(args.action, args.name)


def process(action: str, name: str):
    eval(f'{action.lower()}(\'{name.lower()}\')')


def exist_path(path) -> bool:
    if not os.path.exists(path):
        print(COLOR_ERROR + f"{path} not exists.")
        return False
    return True


def status(name):
    print(COLOR_START + "Start status.")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if name != '' and name != repo['abbr'].lower():
            continue

        root = repo['local'] + repo['name']
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Checking {root}:")

        if not exist_path(root):
            continue

        os.chdir(root)
        os.system('git status')

    print(COLOR_FINISH + "Finish status.")


def clone(name):
    print(COLOR_START + "Start clone.")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if name != '' and name != repo['abbr'].lower():
            continue

        root = repo['local'] + repo['name']
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Cloning {root}:")

        if os.path.exists(root):
            print(COLOR_INFO + f"{root} already exists.")
            continue

        if not os.path.exists(repo['local']):
            os.mkdir(repo['local'])
        os.chdir(repo['local'])
        os.system(f'git clone {repo['remote'][repo['upstream']]} "{repo['name']}"')
        os.chdir(repo['name'])
        os.system(f'git remote rename origin {repo['upstream']}')
        for host, url in repo['remote'].items():
            if host != repo['upstream']:
                os.system(f'git remote add {host} {url}')

    print(COLOR_FINISH + "Finish clone.")


def push(name):
    print(COLOR_START + "Start push.")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if name != '' and name != repo['abbr'].lower():
            continue

        root = repo['local'] + repo['name']
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Pushing {root}:")

        if not exist_path(root):
            continue

        os.chdir(root)
        for host in repo['remote']:
            print(COLOR_INFO + f"to {host}:")
            os.system(f'git push {host}')

    print(COLOR_FINISH + "Finish push.")


def pull(name):
    print(COLOR_START + "Start pull.")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if name != '' and name != repo['abbr'].lower():
            continue

        root = repo['local'] + repo['name']
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Pulling {root}:")

        if not exist_path(root):
            continue

        os.chdir(root)
        os.system(f'git pull')

    print(COLOR_FINISH + "Finish pull.")


def clean(name):
    print(COLOR_START + "Start clean.")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if name != '' and name != repo['abbr'].lower():
            continue

        root = repo['local'] + repo['name']
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Cleaning {root}:")

        if not exist_path(root):
            continue

        if repo['clean']:
            os.chdir(root)
            os.system('git clean -d -f -X')
        else:
            print(COLOR_INFO + "Skip.")

    print(COLOR_FINISH + "Finish clean.")


def remote(name):
    print(COLOR_START + "Start remote.")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if name != '' and name != repo['abbr'].lower():
            continue

        root = repo['local'] + repo['name']
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Showing {root}:")

        if not exist_path(root):
            continue

        os.chdir(root)
        os.system('git remote --verbose')

    print(COLOR_FINISH + "Finish remote.")


def gc(name):
    print(COLOR_START + "Start gc.")

    for i, repo in zip(range(SIZE), DATA['repos']):
        if name != '' and name != repo['abbr'].lower():
            continue

        root = repo['local'] + repo['name']
        print(COLOR_INFO + f"({i + 1}/{SIZE}) Optimizing {root}:")

        if not exist_path(root):
            continue

        os.chdir(root)
        os.system('git gc --aggressive')

    print(COLOR_FINISH + "Finish gc.")


if __name__ == '__main__':
    main()
