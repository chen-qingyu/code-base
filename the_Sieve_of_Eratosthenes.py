def sequence():
    n = 1
    while True:
        n += 1
        yield n


def filter_function(n):
    return lambda x: x % n > 0


def primes():
    it = sequence()
    while True:
        n = next(it)
        yield n
        it = filter(filter_function(n), it)


print("primes less than 100:")
for n in primes():
    if n < 100:
        print(n)
    else:
        break
