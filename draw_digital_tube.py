from turtle import *
from time import *


def drawLine(draw):
    pd() if draw else pu()
    fd(40)
    right(90)


def drawDigit(digit):
    drawLine(True) if digit in [2, 3, 4, 5, 6, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 1, 3, 4, 5, 6, 7, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 2, 3, 5, 6, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 2, 6, 8] else drawLine(False)
    left(90)
    drawLine(True) if digit in [0, 4, 5, 6, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 2, 3, 5, 6, 7, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 1, 2, 3, 4, 7, 8, 9] else drawLine(False)
    left(180)
    pu()
    fd(20)


def turnright(der):
    if der:
        rt(90)
        fd(40)
        lt(90)
    else:
        lt(90)
        fd(40)
        rt(90)


def drawDate(date):
    pencolor("red")
    for i in date:
        if i == '-':
            turnright(1)
            write('年', font=("黑体", 50, "normal"))
            pencolor("green")
            turnright(0)
            fd(80)
        elif i == '=':
            turnright(1)
            write('月', font=("黑体", 50, "normal"))
            pencolor("blue")
            turnright(0)
            fd(80)
        elif i == '+':
            turnright(1)
            write('日', font=("黑体", 50, "normal"))
        else:
            drawDigit(eval(i))


def main():
    tracer(50)
    setup(800, 350, 200, 200)
    hideturtle()
    pu()
    fd(-300)
    pensize(5)
    drawDate(strftime('%Y-%m=%d+', gmtime()))
    done()
    update()


main()
