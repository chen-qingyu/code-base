"""
Copyright (c) 2022.
FileName: draw_rotated_triangle.py
Brief: 绘制一个超好看的图形——三角旋塔（初中时无聊在纸上画的，如今用计算机加持一下）
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.05
"""

import turtle
import math
import random

# 图形大小
L = 700

# 密度
density = 100

# Initial
turtle.title("Rotated Triangle")
turtle.setup(L * 1.1, L * 1.1)
turtle.tracer(100)  # Accelerate the drawing
turtle.mode("standard")  # Initial turtle heading: to the right (east), positive angles: counterclockwise
turtle.colormode(255)
turtle.radians()  # Set the angle measurement units to radians
done = False


def init():
    turtle.penup()
    turtle.hideturtle()


def draw(r: list[float], g: list[float], b: list[float]):
    global done
    done = False

    size = L

    turtle.goto(0, size / 2)
    turtle.setheading(-math.pi / 3)
    for i in range(255):
        delta = size / density
        beta = math.atan(((size - delta) * math.cos(math.pi / 3) - delta) / ((size - delta) * math.sin(math.pi / 3)))
        alpha = math.pi / 6 - beta
        turtle.fillcolor(r[i], g[i], b[i])
        turtle.begin_fill()
        for _ in range(3):
            turtle.forward(size)
            turtle.right(2 * math.pi / 3)
        turtle.end_fill()
        turtle.forward(delta)
        turtle.right(alpha)
        size = ((size - delta) * math.sin(math.pi / 3)) / math.cos(beta)

    done = True
    turtle.update()


# 颜色序列生成函数
def color_gen() -> (list[float], list[float], list[float]):
    # 颜色序列组
    f = (list(range(0, 256, 1)), list(range(255, -1, -1)), [0 for _ in range(256)], [255 for _ in range(256)])

    r = f[random.randint(0, len(f) - 1)]
    g = f[random.randint(0, len(f) - 1)]
    b = f[random.randint(0, len(f) - 1)]

    return r, g, b


# 左击事件处理函数——换图形颜色
def onclick_left(_, __) -> None:
    if done:
        turtle.resetscreen()
        init()
        draw(color_gen()[0], color_gen()[1], color_gen()[2])


# 右击事件处理函数——换背景颜色
def onclick_right(_, __) -> None:
    turtle.bgcolor(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))


if __name__ == '__main__':
    init()
    draw(list(range(256)), list(range(256)), list(range(256)))
    turtle.goto(0, -L / 2)
    turtle.write("左键换图形颜色，右键换背景颜色，请欣赏吧~", align="center", font=('楷体', 16, 'normal'))

    turtle.onscreenclick(onclick_left)
    turtle.onscreenclick(onclick_right, btn=3)

    turtle.mainloop()
