"""
Copyright (c) 2022.
FileName: drawJapanFlag.py
Brief: 绘制日本国旗。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.05.18
"""

import turtle

# 此变量唯一决定旗面大小
UNIT = 25

WIDTH = UNIT * 30  # 旗面宽度
HEIGHT = UNIT * 20  # 旗面高度

# 中心圆半径（Radius）
R = HEIGHT * (3 / 5) / 2

# 颜色 https://www.schemecolor.com/japan-flag-colors.php
colors = {"White": "#FFFFFF", "Crimson Glory": "#BC002D"}

# Initial
turtle.mode("standard")  # Initial turtle heading: to the right (east), positive angles: counterclockwise
turtle.speed("fast")
turtle.title("日本国旗")
turtle.setup(WIDTH * 1.1, HEIGHT * 1.1)
turtle.bgcolor("#F0F0F0")
turtle.penup()

# Draw
turtle.fillcolor(colors["White"])
turtle.goto(-WIDTH / 2, HEIGHT / 2)
turtle.setheading(0)
turtle.begin_fill()
for i in range(2):
    turtle.forward(WIDTH)
    turtle.right(90)
    turtle.forward(HEIGHT)
    turtle.right(90)
turtle.end_fill()

turtle.fillcolor(colors["Crimson Glory"])
turtle.goto(0, -R)
turtle.setheading(0)
turtle.begin_fill()
turtle.circle(R)
turtle.end_fill()

turtle.hideturtle()
turtle.mainloop()
