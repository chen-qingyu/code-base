"""
Copyright (c) 2022.
FileName: drawJapanFlag.py
Brief: 依据 https://en.wikipedia.org/wiki/Flag_of_Japan 绘制日本国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.05.18
"""

import turtle

import mytools

# 此变量唯一决定旗面大小
UNIT = 25

WIDTH = UNIT * 30  # 旗面宽度
HEIGHT = UNIT * 20  # 旗面高度

# 中心圆半径 (Radius)
R = HEIGHT * (3 / 5) / 2

# 颜色 https://www.schemecolor.com/japan-flag-colors.php
colors = {"White": "#FFFFFF", "Crimson Glory": "#BC002D"}

# Initial
mytools.init_environment("日本国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
mytools.draw_rect(-WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT, colors["White"])

mytools.draw_circle((0, 0), R, colors["Crimson Glory"])

# Done
turtle.mainloop()
