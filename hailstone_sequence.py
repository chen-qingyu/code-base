import matplotlib.pyplot as plt


def hailstone(x: int):
    ls = [x]
    while x > 1:
        if x % 2 == 1:
            x = x * 3 + 1
        else:
            x //= 2
        ls.append(x)
    return ls


plt.stem(hailstone(27))
plt.show()
