"""
Copyright (c) 2022.
FileName: drawUnitedStatesOfAmericaFlag.py
Brief: 绘制美国国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.05.18
"""

import turtle
import math

# 此变量唯一决定旗面相对大小
UNIT = 25  # 标准国旗尺寸纵向30/横向20等分方格边长

WIDTH = UNIT * 38  # 旗面宽度
HEIGHT = UNIT * 20  # 旗面高度

# 条纹高度
L = HEIGHT / 13

# 蓝色部分
B_W = WIDTH * (2 / 5)  # 宽度
B_H = HEIGHT * (7 / 13)  # 高度

B_T = B_H / 10  # 横向等分线
B_L = B_W / 12  # 纵向等分线

# 五角星外接圆半径
R = 0.0616 * HEIGHT / 2


def my_range(start: float, stop: float, step: float = 1) -> list[float, ...]:
    ls = []
    while start < stop:
        ls.append(start)
        start += step
    return ls


# 等分线交叉点（非常优雅）
B_C = [[(-WIDTH / 2 + x, HEIGHT / 2 - y) for x in my_range(B_L, B_W, B_L)] for y in my_range(B_T, B_H, B_T)]
B_C = sum(B_C, [])  # 嵌套list展开铺平

# 颜色 https://www.schemecolor.com/united-states-of-america-flag-colors.php
colors = {"American Blue": "#3C3B6E", "White": "#FFFFFF", "American Red": "#B22234"}

# Initial
turtle.mode("standard")  # Initial turtle heading: to the right (east), positive angles: counterclockwise
turtle.speed("fastest")
turtle.title("美国国旗")
turtle.setup(WIDTH * 1.1, HEIGHT * 1.1)
turtle.bgcolor("#FAFAFA")
turtle.penup()

# Draw
for i in range(13):
    turtle.goto(-WIDTH / 2, HEIGHT / 2 - L * i)
    turtle.setheading(0)
    turtle.fillcolor(colors["American Red" if i % 2 == 0 else "White"])
    turtle.begin_fill()
    for j in range(2):
        turtle.forward(WIDTH)
        turtle.right(90)
        turtle.forward(L)
        turtle.right(90)
    turtle.end_fill()

turtle.fillcolor(colors["American Blue"])
turtle.goto(-WIDTH / 2, HEIGHT / 2)
turtle.setheading(0)
turtle.begin_fill()
for i in range(2):
    turtle.forward(B_W)
    turtle.right(90)
    turtle.forward(B_H)
    turtle.right(90)
turtle.end_fill()

turtle.fillcolor(colors["White"])
i = 0
for x, y in B_C:
    turtle.goto(x, y + R)
    if i % 2 == 0:
        turtle.setheading(-(90 - 18))
        turtle.begin_fill()
        for j in range(5):
            turtle.forward(R * 2 * math.cos(18))
            turtle.right(144)
        turtle.end_fill()
    i += 1

turtle.hideturtle()
turtle.mainloop()
