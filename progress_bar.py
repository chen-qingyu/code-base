from time import perf_counter, sleep

scale = 50
print("START".center(scale // 2, "-"))

start = perf_counter()
for i in range(scale + 1):
    a = '*' * i
    b = '.' * (scale - i)
    c = i / scale
    d = perf_counter() - start
    print("{:6.1%}[{}->{}] {:.2f} s".format(c, a, b, d), end="\r")
    sleep(0.02)

print("\n" + "END".center(scale // 2, "-"))
input()
