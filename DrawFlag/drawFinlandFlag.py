"""
Copyright (c) 2022.
FileName: drawFinlandFlag.py
Brief: 依据 https://en.wikipedia.org/wiki/Flag_of_Finland 绘制芬兰国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.13
"""

import turtle

import mytools

# 此变量唯一决定旗面大小
UNIT = 40

WIDTH = 18 * UNIT  # 旗面宽度
HEIGHT = 11 * UNIT  # 旗面高度

# 颜色 https://www.schemecolor.com/finland-flag-colors.php
colors = {"Dark Midnight Blue": "#002F6C", "White": "#FFFFFF"}

# Initial
mytools.init_environment("芬兰国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
mytools.draw_rect(-WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT, colors["White"])
mytools.draw_rect(-WIDTH / 2, HEIGHT / 2 - HEIGHT * (4 / 11), WIDTH, HEIGHT * (3 / 11), colors["Dark Midnight Blue"])
mytools.draw_rect(-WIDTH / 2 + WIDTH * (5 / 18), HEIGHT / 2, WIDTH * (3 / 18), HEIGHT, colors["Dark Midnight Blue"])

# Done
turtle.mainloop()
