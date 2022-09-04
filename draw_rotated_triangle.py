"""
Copyright (c) 2022.
FileName: draw_rotated_triangle.py
Brief: 绘制一个超好看的图形
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.05
"""

import turtle
import math

# 此变量决定图形大小
L = 700

# 此变量决定层数
deep = 200

# 此变量决定密度
density = 50

# Initial
turtle.mode("standard")  # Initial turtle heading: to the right (east), positive angles: counterclockwise
turtle.speed("fastest")
turtle.title("Rotated triangle")
turtle.setup(L * 1.1, L * 1.1)
turtle.bgcolor("white")
turtle.colormode(255)
turtle.radians()  # Set the angle measurement units to radians
turtle.penup()
turtle.hideturtle()
turtle.tracer(2) # Accelerate the drawing

# Draw
turtle.goto(0, L / 2)
turtle.setheading(-math.pi / 3)
for g in range(255, 0, -255 // deep):
    delta = L / density
    beta = math.atan(((L - delta) * math.cos(math.pi / 3) - delta) / ((L - delta) * math.sin(math.pi / 3)))
    alpha = math.pi / 6 - beta
    turtle.fillcolor(0, g, 255)
    turtle.begin_fill()
    for i in range(3):
        turtle.forward(L)
        turtle.right(2 * math.pi / 3)
    turtle.end_fill()
    turtle.forward(delta)
    turtle.right(alpha)
    L = ((L - delta) * math.sin(math.pi / 3)) / math.cos(beta)

turtle.mainloop()
