"""
Copyright (c) 2022.
FileName: drawGermanyFlag.py
Brief: 依据 https://en.wikipedia.org/wiki/Flag_of_Germany 绘制德国国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.14
"""

import turtle

import mytools

# 此变量唯一决定旗面大小
UNIT = 15

WIDTH = UNIT * 50  # 旗面宽度
HEIGHT = UNIT * 30  # 旗面高度

# 颜色 https://www.schemecolor.com/germany-flag-colors.php
colors = {"Black": "#000000", "Electric Red": "#DD0000", "Tangerine Yellow": "#FFCE00"}

# Initial
mytools.init_environment("德国国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
for (i, color) in enumerate(colors.keys()):
    mytools.draw_rect(-WIDTH / 2, HEIGHT * (1 / 2 - i / 3), WIDTH, HEIGHT / 3, colors[color])

# Done
turtle.mainloop()
