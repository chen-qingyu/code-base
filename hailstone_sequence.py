import pprint


def hailstone(n):
    length = 1
    seq = [n]
    while n > 1:
        if n % 2 == 1:
            n = n * 3+1
        else:
            n //= 2
        seq.append(n)
    return seq


pprint.pprint(hailstone(27))
