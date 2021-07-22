for i in range(1, 256):
    str = bin(i).replace("0b", "").replace("0", " ").replace("1", "*")
    while len(str) != 32:
        str = " " + str
    print("{:3d}{}".format(i, str))
input()
