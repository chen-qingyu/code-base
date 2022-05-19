for i in range(1, 10):
    for j in range(1, i + 1):
        print(" {} x {} = {:2d} |".format(i, j, i * j), end="")
        if i == j:
            print('\n' + "-------------" * i)
