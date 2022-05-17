"""
Copyright (c) 2022.
FileName: draw_theFiveStarredRedFlag.py
Brief: 依据中华人民共和国国家标准GB 12982-2004《国旗》绘制五星红旗
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.05.17
"""

import turtle
import math

# 此变量唯一决定旗面相对大小
UNIT = 25  # 标准国旗尺寸纵向30/横向20等分方格边长

WIDTH = UNIT * 30  # 旗面宽度
HEIGHT = UNIT * 20  # 旗面高度


class Point:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def distance_to(self, other) -> float:
        return math.sqrt((self.x - other.x) ** 2 + (self.y - other.y) ** 2)


# 五角星中心点坐标（以旗面中心为原点，X轴正向向右，Y轴正向向上）
# 一开始是以左上角为原点，X轴正向向右，Y轴正向向下的，各个坐标计算好后准备写代码，但是turtle库居然不支持这种坐标系，无奈只好重新设计了
C = [
    Point(UNIT * -10, UNIT * 5),  # 主星中心点
    Point(UNIT * -5, UNIT * 8),  # 纵向第一个小五角星中心点
    Point(UNIT * -3, UNIT * 6),  # 纵向第二个小五角星中心点
    Point(UNIT * -3, UNIT * 3),  # 纵向第三个小五角星中心点
    Point(UNIT * -5, UNIT * 1),  # 纵向第四个小五角星中心点
]

# 五角星外接圆半径
R = [UNIT * i for i in (3, 1, 1, 1, 1)]

# 五角星绘制起始点朝向主星中心的弧度（以X轴正向为0）
T = [
    math.radians(-90),
    math.atan(3 / 5),
    math.atan(1 / 7),
    math.atan(-2 / 7),
    math.atan(-4 / 5),
]

# 五角星绘制起始弧度（以X轴正向为0）
A = [T[i] + math.radians(18) for i in range(len(T))]

# 五角星绘制起始点：主星为上顶点，小五角星为最接近主星的角
S = [Point(C[0].x + (C[0].distance_to(C[i]) - R[i]) * math.cos(T[i]),
           C[0].y + (C[0].distance_to(C[i]) - R[i]) * math.sin(T[i])) for i in range(len(T))]

# 五角星绘制边长长度
L = [R[i] * 2 * math.cos(math.radians(18)) for i in range(len(R))]

# Initial
turtle.mode("standard")  # Initial turtle heading: to the right (east), positive angles: counterclockwise
turtle.radians()  # Set the angle measurement units to radians
turtle.speed("fast")
turtle.title("五星红旗")
turtle.setup(WIDTH, HEIGHT)
turtle.bgcolor("red")
turtle.pencolor("yellow")
turtle.fillcolor("yellow")

# Draw
for i in range(len(C)):
    turtle.penup()
    turtle.goto(S[i].x, S[i].y)
    turtle.setheading(A[i])
    turtle.pendown()
    turtle.begin_fill()
    for j in range(5):
        turtle.forward(L[i])
        turtle.right(math.radians(144))
    turtle.end_fill()
turtle.hideturtle()
turtle.mainloop()
