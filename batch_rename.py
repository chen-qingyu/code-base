import os


def rename(dir_path):
    filelist = os.listdir(dir_path)
    for oldname in filelist:
        newname = oldname.replace(" ", "_")
        os.rename(oldname, newname)


rename(r"F:\Python")
