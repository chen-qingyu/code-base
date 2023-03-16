import os


def clean(path: str = "./"):
    ''' clean up empty directories. '''
    os.chdir(path)
    for root, dirs, files in os.walk(path):
        for d in dirs:
            # delete empty folders recursively
            try:
                if os.listdir(os.path.join(root, d)) == []:
                    os.removedirs(os.path.join(root, d))
                    print(os.path.join(root, d) + " deleted.")
            except Exception as e:
                print(e)


if __name__ == "__main__":
    clean()
