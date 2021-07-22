def fac(n):
    if n == 0:
        return 1
    else:
        return n * fac(n - 1)


print("Please enter a integer to calculate the factorial (otherwise to exit).\n")
try:
    while True:
        n = eval(input())
        if isinstance(n, int):
            if n < 0:
                print("Please enter a positive integer.\n")
                continue
            if n > 20:
                print("%d! is too huge to calculate. >_<\n" % n)
                continue
            print("{}! = {}\n".format(n, fac(n)))
except Exception:
    input("\nBye~")
