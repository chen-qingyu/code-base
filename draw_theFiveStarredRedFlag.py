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
    Point(-WIDTH / 2 + UNIT * 5, HEIGHT / 2 - UNIT * 5),  # 主星中心点
    Point(-WIDTH / 2 + UNIT * 10, HEIGHT / 2 - UNIT * 2),  # 纵向第一个小五角星中心点
    Point(-WIDTH / 2 + UNIT * 12, HEIGHT / 2 - UNIT * 4),  # 纵向第二个小五角星中心点
    Point(-WIDTH / 2 + UNIT * 12, HEIGHT / 2 - UNIT * 7),  # 纵向第三个小五角星中心点
    Point(-WIDTH / 2 + UNIT * 10, HEIGHT / 2 - UNIT * 9),  # 纵向第四个小五角星中心点
]

# 五角星外接圆半径
R = [
    UNIT * 3,
    UNIT * 1,
    UNIT * 1,
    UNIT * 1,
    UNIT * 1,
]

# 五角星朝向主星的弧度（以X轴正向为0）
T = [
    0,
    math.atan(3 / 5),
    math.atan(1 / 7),
    math.atan(-2 / 7),
    math.atan(-4 / 5),
]

# 五角星绘制起始弧度（以X轴正向为0）
A = [
    math.radians(-(90 - 18)),
    T[1] + math.radians(18),
    T[2] + math.radians(18),
    T[3] + math.radians(18),
    T[4] + math.radians(18),
]

# 五角星绘制起始点（以旗面中心为原点，X轴正向向右，Y轴正向向上）
S = [
    Point(C[0].x, C[0].y + UNIT * 3),  # 主星上顶点

    Point(C[0].x + (C[0].distance_to(C[1]) - R[1]) * math.cos(T[1]),
          C[0].y + (C[0].distance_to(C[1]) - R[1]) * math.sin(T[1])),  # 第一颗小五角星最接近主星的角

    Point(C[0].x + (C[0].distance_to(C[2]) - R[2]) * math.cos(T[2]),
          C[0].y + (C[0].distance_to(C[2]) - R[2]) * math.sin(T[2])),  # 第二颗小五角星最接近主星的角

    Point(C[0].x + (C[0].distance_to(C[3]) - R[3]) * math.cos(T[3]),
          C[0].y + (C[0].distance_to(C[3]) - R[3]) * math.sin(T[3])),  # 第三颗小五角星最接近主星的角

    Point(C[0].x + (C[0].distance_to(C[4]) - R[4]) * math.cos(T[4]),
          C[0].y + (C[0].distance_to(C[4]) - R[4]) * math.sin(T[4])),  # 第四颗小五角星最接近主星的角
]

# 五角星绘制边长长度
L = [R[i] * 2 * math.cos(math.radians(18)) for i in range(len(R))]

# Initial
turtle.mode("standard")  # Initial turtle heading: to the right (east), positive angles: counterclockwise
turtle.radians()  # Set the angle measurement units to radians
turtle.speed("normal")
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
