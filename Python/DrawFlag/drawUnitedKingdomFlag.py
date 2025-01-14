"""
Copyright (c) 2022.
FileName: drawUnitedKingdomFlag.py
Brief: 依据 https://en.wikipedia.org/wiki/Flag_of_the_United_Kingdom 绘制英国国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.14
"""

import turtle
import math

import mytools

# 此变量唯一决定旗面大小
UNIT = 15

WIDTH = 60 * UNIT  # 旗面宽度
HEIGHT = 30 * UNIT  # 旗面高度

# 白色 (White) 部分 X 偏移量
W_X = 3 * UNIT / math.sin(math.atan(1 / 2))
# 白色 (White) 部分 Y 偏移量
W_Y = 3 * UNIT / math.cos(math.atan(1 / 2))
# 右下角白色 (White) 部分顶点 (Point)
W_P = [(WIDTH / 2 - W_X, -HEIGHT / 2), (WIDTH / 2, -HEIGHT / 2), (WIDTH / 2, -HEIGHT / 2 + W_Y), (W_X, 0), (-W_X, 0)]

# 红色 (Red) 部分 X 偏移量
R_X = 2 * UNIT / math.sin(math.atan(1 / 2))
# 红色 (Red) 部分 Y 偏移量
R_Y = 2 * UNIT / math.cos(math.atan(1 / 2))
# 右下 (Down) 角红色 (Red) 部分顶点 (Point)
R_P_D = [(WIDTH / 2, -HEIGHT / 2), (WIDTH / 2, -HEIGHT / 2 + R_Y), (R_X, 0), (0, 0)]
# 右上 (Up) 角红色 (Red) 部分顶点 (Point)
R_P_U = [(WIDTH / 2, HEIGHT / 2), (WIDTH / 2 - R_X, HEIGHT / 2), (-R_X, 0), (0, 0)]

# 颜色 https://www.schemecolor.com/united-kingdom-uk-flag-colors.php
colors = {"Catalina Blue": "#00247D", "White": "#FFFFFF", "Philippine Red": "#CF142B"}

# Initial
mytools.init_environment("英国国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
mytools.draw_rect(-WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT, colors["Catalina Blue"])

for w_x, w_y in [(1, 1), (1, -1), (-1, 1), (-1, -1)]:  # 白色部分镜像对称
    mytools.draw_polygon(list(map(lambda p: (w_x * p[0], w_y * p[1]), W_P)), colors["White"])

for r_x, r_y in [(1, 1), (-1, -1)]:  # 红色部分中心对称
    mytools.draw_polygon(list(map(lambda p: (r_x * p[0], r_y * p[1]), R_P_D)), colors["Philippine Red"])
    mytools.draw_polygon(list(map(lambda p: (r_x * p[0], r_y * p[1]), R_P_U)), colors["Philippine Red"])

mytools.draw_rect(-30 * UNIT, 5 * UNIT, 60 * UNIT, 10 * UNIT, colors["White"])
mytools.draw_rect(-5 * UNIT, 15 * UNIT, 10 * UNIT, 30 * UNIT, colors["White"])
mytools.draw_rect(-30 * UNIT, 3 * UNIT, 60 * UNIT, 6 * UNIT, colors["Philippine Red"])
mytools.draw_rect(-3 * UNIT, 15 * UNIT, 6 * UNIT, 30 * UNIT, colors["Philippine Red"])

# Done
turtle.mainloop()
