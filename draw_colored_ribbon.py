import turtle
import math
import random

# 此变量决定色带宽度
L = 100

# Initial
turtle.title("Colored Ribbon")
turtle.tracer(100)  # Accelerate the drawing
turtle.mode("standard")  # Initial turtle heading: to the right (east), positive angles: counterclockwise
turtle.colormode(255)
turtle.bgcolor("#FAFAFA")
turtle.setup(1280, 720)
turtle.penup()
turtle.hideturtle()
turtle.pensize(1)


# 数字范围映射
def num_map(x, x_min, x_max, y_min, y_max):
    slope = (y_max - y_min) / (x_max - x_min)
    return y_min + round(slope * (x - x_min))


# range函数拓展版，支持range函数所有功能加上浮点数
def my_range(start: float, stop: float, step: float = 1) -> list[float, ...]:
    ls = []
    while (start < stop) if step > 0 else (start > stop):
        ls.append(start)
        start += step
    return ls


# Draw
# 总长度 255*3 左闭右开
zero = lambda n: [0 for _ in range(n)]

up = lambda n: list(range(0, 255, 255 // n))
down = lambda n: list(range(255, 0, -255 // n))

sin_up = lambda: [int(255 * math.sin(x)) for x in my_range(0, math.pi / 2, (math.pi / 2) / 255)]
sin_down = lambda: [int(255 * math.sin(x)) for x in my_range(math.pi / 2, math.pi, (math.pi / 2) / 255)]

r = []
g = []
b = []

# 0. 参考
r.append(down(255 // 2 + 1) + zero(255 * 2) + up(255 // 2 + 1))
g.append(zero(255 // 2) + up(255 // 2) + down(255 // 2 + 1) + zero(255 * 3 // 2))
b.append(zero(255 * 3 // 2) + up(255 // 2) + down(255 // 2 + 1) + zero(255 // 2))

# 1. 直线彩虹
r.append(down(255) + zero(255) + up(255))
g.append(up(255) + down(255) + zero(255))
b.append(zero(255) + up(255) + down(255))

# 2. 正弦彩虹
r.append(sin_down() + zero(255) + sin_up())
g.append(sin_up() + sin_down() + zero(255))
b.append(zero(255) + sin_up() + sin_down())

for index in range(3):
    for i in range(255 * 3):
        turtle.goto(i - 500, 100 - index * 100)
        turtle.setheading(90)
        turtle.pencolor(r[index][i], g[index][i], b[index][i])
        turtle.pendown()
        turtle.forward(L)
        turtle.penup()

turtle.mainloop()
