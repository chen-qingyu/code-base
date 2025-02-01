"""
Copyright (c) 2022.
FileName: drawSingaporeFlag.py
Brief: 依据 https://en.wikipedia.org/wiki/Flag_of_Singapore 绘制新加坡国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.06
"""

import turtle
import math

import mytools

# 此变量唯一决定旗面大小
UNIT = 14

WIDTH = UNIT * 54  # 旗面宽度
HEIGHT = UNIT * 36  # 旗面高度

# 新月 (Moon) 半径 (Radius)
M_R = (13.25 / 2) * UNIT

# 星环 (Ring) 半径 (Radius)
R_R = (7.6 / 2) * UNIT

# 星星 (Star) 外接圆半径 (Radius)
S_R = (3.45 / 2) * UNIT

# 新月 (Moon) 中心
M = (-WIDTH / 2 + (4.78 + 3 + 7.25 / 2) * UNIT, 9 * UNIT)

# 星环 (Ring) 中心
R = (-WIDTH / 2 + (4.78 + 3 + 7.25) * UNIT, 9 * UNIT)

# 星星 (Star) 中心
S = [(R[0] + R_R * math.sin(i * 2 * math.pi / 5), R[1] + R_R * math.cos(i * 2 * math.pi / 5)) for i in range(5)]

# 颜色 https://www.schemecolor.com/singapore-flag-colors.php
colors = {"Deep Carmine Pink": "#EF3340", "White": "#FFFFFF"}

# Initial
mytools.init_environment("新加坡国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
for (i, color) in enumerate(colors.keys()):
    mytools.draw_rect(-WIDTH / 2, HEIGHT * (1 / 2 - i / 2), WIDTH, HEIGHT / 2, colors[color])

mytools.draw_circle(M, M_R, colors["White"], steps=720)
mytools.draw_circle(R, M_R, colors["Deep Carmine Pink"], steps=720)

for i in range(len(S)):
    mytools.draw_star(S[i], S_R, colors["White"])

# Done
turtle.mainloop()
