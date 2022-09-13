"""
Copyright (c) 2022.
FileName: drawCanadaFlag.py
Brief: 依据 https://en.wikipedia.org/wiki/Flag_of_Canada 绘制加拿大国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.13
"""

import turtle

import mytools

# 此变量唯一决定旗面大小
UNIT = 0.6

WIDTH = 960 * 2 * UNIT  # 旗面宽度
HEIGHT = 480 * 2 * UNIT  # 旗面高度

# 锚定点 (Point)
P = [(-18, -406), (-8.955, -233.418), (-31.229, -213.712), (-203, -244), (-179.705, -179.999), (-183.740, -165.450),
     (-372, -13), (-329.678, 6.735), (-322.808, 22.534), (-360, 137), (-251.637, 113.967), (-236.968, 121.603),
     (-216, 171), (-131.369, 80.245), (-109.101, 91.591), (-150, 302), (-84.543, 264.208), (-66.460, 269.565), (0, 400)]
P = P + [(-P[len(P) - i - 1][0], P[len(P) - i - 1][1]) for i in range(len(P))]  # 轴对称翻转
P = list(map(lambda p: (p[0] * UNIT, p[1] * UNIT), P))  # 比例放大

# 锚定圆心 (Centre)
C = [(-27.929, -232.423), (-191.921, -175.553), (-335.172, 18.517), (-248.934, 126.683), (-121.862, 89.111),
     (-78.043, 275.467)]
C = C + [(-C[len(C) - i - 1][0], C[len(C) - i - 1][1]) for i in range(len(C))]  # 轴对称翻转
C = list(map(lambda p: (p[0] * UNIT, p[1] * UNIT), C))  # 比例放大

# 半径 (Radius)
R = [19, 13, 13, 13, 13, 13]
R = R + R[::-1]  # 轴对称翻转
R = list(map(lambda r: r * UNIT, R))  # 比例放大

# 颜色 https://www.schemecolor.com/canada-flag-colors.php
colors = {"Red": "#FF0000", "White": "#FFFFFF"}

# Initial
mytools.init_environment("加拿大国旗", WIDTH * 1.1, HEIGHT * 1.1)

# Draw
mytools.draw_rect(-960 * UNIT, 480 * UNIT, (960 - 480) * UNIT, HEIGHT, colors["Red"])
mytools.draw_rect(-480 * UNIT, 480 * UNIT, 480 * 2 * UNIT, 480 * 2 * UNIT, colors["White"])
mytools.draw_rect(480 * UNIT, 480 * UNIT, (960 - 480) * UNIT, HEIGHT, colors["Red"])

mytools.draw_polygon(P, colors["Red"])

for i in range(len(C)):
    mytools.draw_circle(C[i][0], C[i][1], R[i], colors["White"])

# Done
turtle.mainloop()
