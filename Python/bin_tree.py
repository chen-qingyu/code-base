for i in range(256):
    print("{:3d}{}".format(i, bin(i)[2:].replace("0", " ").replace("1", "*").rjust(16)))
