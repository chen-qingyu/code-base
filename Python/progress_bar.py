from time import perf_counter, sleep

scale = 50
start = perf_counter()
for i in range(scale + 1):
    print(f"{i / scale:6.1%} [{'>' * i}{'.' * (scale - i)}] {perf_counter() - start:.2f} s", end="\r")
    sleep(0.01)
