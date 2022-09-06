"""
Copyright (c) 2022.
FileName: drawPeoplesRepublicOfChinaFlag.py
Brief: 依据中华人民共和国国家标准GB 12982-2004《国旗》绘制五星红旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.05.17
"""

import turtle
import math

import mytools

# 此变量唯一决定旗面大小
UNIT = 25  # 标准国旗尺寸纵向30/横向20等分方格边长

WIDTH = UNIT * 30  # 旗面宽度
HEIGHT = UNIT * 20  # 旗面高度

# 五角星中心点 (Center) 坐标 (以旗面中心为原点，X轴正向向右，Y轴正向向上)
C = [
    (UNIT * -10, UNIT * 5),  # 主星中心点
    (UNIT * -5, UNIT * 8),  # 纵向第一个小五角星中心点
    (UNIT * -3, UNIT * 6),  # 纵向第二个小五角星中心点
    (UNIT * -3, UNIT * 3),  # 纵向第三个小五角星中心点
    (UNIT * -5, UNIT * 1),  # 纵向第四个小五角星中心点
]

# 五角星外接圆半径 (Radius)
R = [UNIT * i for i in (3, 1, 1, 1, 1)]

# 五角星上顶点过该五角星中心到主星中心的连线与y轴的夹角弧度 (Angle)
A = [
    0,
    math.pi / 2 + math.atan(3 / 5),
    math.pi / 2 + math.atan(1 / 7),
    math.pi / 2 + math.atan(-2 / 7),
    math.pi / 2 + math.atan(-4 / 5),
]

# 颜色 https://www.schemecolor.com/peoples-republic-of-china-flag-colors.php
colors = {"Maximum Red": "#DE2910", "Golden Yellow": "#FFDE00"}

# Initial
mytools.init_environment("五星红旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
mytools.draw_rect(-WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT, colors["Maximum Red"])

for i in range(len(C)):
    mytools.draw_star(C[i][0], C[i][1], R[i], colors["Golden Yellow"], A[i])

# Done
turtle.mainloop()
