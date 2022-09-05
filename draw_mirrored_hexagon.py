"""
Copyright (c) 2022.
FileName: draw_mirrored_hexagon.py
Brief: 绘制一个超好看的图形——六芒境域（初中时无聊在纸上画的，如今用计算机加持一下）
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.05
"""

import turtle
import math
import random

# 此变量决定图形大小
L = 700

# 此变量决定密度
density = 10

# Initial
turtle.title("Mirrored Hexagon")
turtle.setup(L * 1.1, L * 1.1)
turtle.tracer(10)  # Accelerate the drawing
turtle.mode("standard")  # Initial turtle heading: to the right (east), positive angles: counterclockwise
turtle.colormode(255)
turtle.radians()  # Set the angle measurement units to radians
done = False


def init() -> None:
    turtle.penup()
    turtle.hideturtle()


# Draw
def draw(r: list[float], g: list[float], b: list[float]):
    global done
    done = False

    size = L

    for loop in range(density):
        radius = size / 2

        # 画圆
        turtle.goto(0, radius)
        turtle.setheading(math.pi)
        turtle.fillcolor(r[loop * 256 // density], r[loop * 256 // density], r[loop * 256 // density])
        turtle.begin_fill()
        turtle.circle(radius)
        turtle.end_fill()

        # 画六边形
        turtle.goto(0, radius)
        turtle.fillcolor(g[loop * 256 // density], g[loop * 256 // density], g[loop * 256 // density])
        turtle.begin_fill()
        for i in range(6):
            turtle.setheading((-math.pi / 6) + i * (-math.pi / 3))
            turtle.forward(radius)
        turtle.end_fill()

        # 画六芒星
        for i in [1, -1]:
            turtle.goto(0, i * radius)
            turtle.fillcolor(b[loop * 256 // density], b[loop * 256 // density], b[loop * 256 // density])
            turtle.begin_fill()
            for j in range(3):
                turtle.setheading(-i * (math.pi / 3 + j * (2 * math.pi / 3)))
                turtle.forward(math.sqrt(3) * radius)
            turtle.end_fill()

        size /= 2

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
    turtle.goto(-L / 2, L / 2)
    turtle.write("万花筒，请欣赏~  By 青羽", align="left", font=('楷体', 16, 'normal'))

    turtle.onscreenclick(onclick_left)
    turtle.onscreenclick(onclick_right, btn=3)

    turtle.mainloop()
