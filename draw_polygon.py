from turtle import *


def init():
    setup(500, 500)
    window = Screen()
    window.bgcolor("black")
    pencolor("white")
    hideturtle()
    speed(50)


def draw(side):
    for i in range(18):
        for j in range(side):
            fd(360 / side)
            rt(360 / side)
        rt(20)


side = eval(input("Please input the side (2-36): "))
while side < 2 or side > 36:
    side = eval(input("Please input the side (2-36): "))
init()
draw(side)
'''
pu()
goto(0, -200)
pd()
write('@ 青羽', font=("楷体", 16, "normal"))
'''
done()
