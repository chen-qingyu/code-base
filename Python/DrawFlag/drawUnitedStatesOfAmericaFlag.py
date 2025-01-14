"""
Copyright (c) 2022.
FileName: drawUnitedStatesOfAmericaFlag.py
Brief: 依据 https://en.wikipedia.org/wiki/Flag_of_the_United_States 绘制美国国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.05.18
"""

import turtle

import mytools

# 此变量唯一决定旗面大小
UNIT = 25

WIDTH = UNIT * 38  # 旗面宽度
HEIGHT = UNIT * 20  # 旗面高度

# 条纹 (Stripe) 高度 (Height)
S_H = HEIGHT / 13

# 蓝色横幅 (Banner) 部分
B_W = WIDTH * (2 / 5)  # 宽度 (Width)
B_H = HEIGHT * (7 / 13)  # 高度 (Height)
B_V = B_W / 12  # 纵向 (Vertical) 等分线
B_T = B_H / 10  # 横向 (Transverse) 等分线

# 横纵等分线交点 (Intersection) ，嵌套list comprehension展开铺平并过滤，非常优雅的写法！
B_I = sum([[(-WIDTH / 2 + x, HEIGHT / 2 - y) for x in mytools.my_range(B_V, B_W, B_V)] for y in mytools.my_range(B_T, B_H, B_T)], [])[::2]

# 五角星外接圆半径 (Radius)
R = 0.0616 * HEIGHT / 2

# 颜色 https://www.schemecolor.com/united-states-of-america-flag-colors.php
colors = {"American Blue": "#3C3B6E", "White": "#FFFFFF", "American Red": "#B22234"}

# Initial
mytools.init_environment("美国国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
for i in range(13):
    mytools.draw_rect(-WIDTH / 2, HEIGHT / 2 - S_H * i, WIDTH, S_H, colors["American Red" if i % 2 == 0 else "White"])

mytools.draw_rect(-WIDTH / 2, HEIGHT / 2, B_W, B_H, colors["American Blue"])

for x, y in B_I:
    mytools.draw_star(x, y, R, colors["White"])

# Done
turtle.mainloop()
