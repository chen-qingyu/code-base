from turtle import *


def koch(size, n):
    if n == 0:
        fd(size)
    else:
        for angle in [0, 60, -120, 60]:
            lt(angle)
            koch(size / 3, n - 1)


def main(level):
    setup(600, 600)
    pu()
    goto(-200, 100)
    pd()
    koch(400, level)
    rt(120)
    koch(400, level)
    rt(120)
    koch(400, level)
    hideturtle()
    done()


num = eval(input("Please input 2 - 4: "))
main(num)
