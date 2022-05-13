def fac(n: int) -> int:
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
                print("Please enter a positive integer.>_<\n")
                continue
            print("{}! = {}\n".format(n, fac(n)))
except Exception:
    print("\nBye~")
