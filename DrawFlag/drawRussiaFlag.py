"""
Copyright (c) 2022.
FileName: drawRussiaFlag.py
Brief: 绘制俄罗斯国旗。
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

# 颜色 https://www.schemecolor.com/russia-flag-colors.php
colors = {"White": "#FFFFFF", "Dark Powder Blue": "#0033A0", "Maximum Red": "#DA291C"}

# Initial
mytools.init_environment("俄罗斯国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
index = 0
for color in colors.keys():
    mytools.draw_rect(-WIDTH / 2, HEIGHT * (1 / 2 - index / len(colors)), WIDTH, HEIGHT / len(colors), colors[color])
    index += 1

# Done
turtle.mainloop()
