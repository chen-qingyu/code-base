import functools


def hamming(bits):
    return functools.reduce(lambda x, y: x ^ y, [i for (i, b) in enumerate(bits) if b])


bits = [0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0]
print(bits)
print(hamming(bits))
bits[9] ^= 1
print(hamming(bits))
print(bits)
