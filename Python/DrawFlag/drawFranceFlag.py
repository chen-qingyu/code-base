"""
Copyright (c) 2022.
FileName: drawFranceFlag.py
Brief: 依据 https://en.wikipedia.org/wiki/Flag_of_France 绘制法国国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.13
"""

import turtle

import mytools

# 此变量唯一决定旗面大小
UNIT = 25

WIDTH = 30 * UNIT  # 旗面宽度
HEIGHT = 20 * UNIT  # 旗面高度

# 颜色 https://www.schemecolor.com/france-flag-colors.php
colors = {"USAFA Blue": "#0055A4", "White": "#FFFFFF", "Cinnabar": "#EF4135"}

# Initial
mytools.init_environment("法国国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
for (i, color) in enumerate(colors.keys()):
    mytools.draw_rect(WIDTH * (-1 / 2 + i / 3), HEIGHT / 2, WIDTH / 3, HEIGHT, colors[color])

# Done
turtle.mainloop()
