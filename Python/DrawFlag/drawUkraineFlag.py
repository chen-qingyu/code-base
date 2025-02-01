"""
Copyright (c) 2022.
FileName: drawUkraineFlag.py
Brief: 依据 https://en.wikipedia.org/wiki/Flag_of_Ukraine 绘制乌克兰国旗。
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

# 颜色 https://www.schemecolor.com/ukraine-flag-colors.php
colors = {"Sapphire": "#005BBB", "Cyber Yellow": "#FFD500"}

# Initial
mytools.init_environment("乌克兰国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
for (i, color) in enumerate(colors.keys()):
    mytools.draw_rect(-WIDTH / 2, HEIGHT * (1 / 2 - i / 2), WIDTH, HEIGHT / 2, colors[color])

# Done
turtle.mainloop()
