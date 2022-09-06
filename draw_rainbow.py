import turtle
import math

# Initial
WIDTH = 1920
HEIGHT = 1080 - 80
turtle.title("Colored Ribbon")
turtle.tracer(10000)  # Accelerate the drawing
turtle.mode("standard")  # Initial turtle heading: to the right (east), positive angles: counterclockwise
turtle.colormode(255)
turtle.setup(WIDTH, HEIGHT, 0, 0)
turtle.penup()
turtle.hideturtle()
turtle.pensize(1)
grass_height = 200


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


# RGB颜色分量映射算子 from begin to end divided to |begin-end| parts. begin, end belongs [0, 255]
zero = lambda n: [0 for _ in range(n)]
linear = lambda begin, end, parts: my_range(begin, end, (end - begin) / parts)
sin_up = lambda: [int(255 * math.sin(x)) for x in my_range(0, math.pi / 2, (math.pi / 2) / 255)]
sin_down = lambda: [int(255 * math.sin(x)) for x in my_range(math.pi / 2, math.pi, (math.pi / 2) / 255)]

colors = {  # https://www.schemecolor.com/shades-of-sky-blue.php
    "Blueberry": (64, 138, 241),  # darker
    "Non-Photo Blue": (168, 215, 250),  # lighter
    "Royal Green": (23, 110, 0),  # darker
    "Green Lizard": (174, 222, 62),  # lighter
}

# sky
r = list(map(int, linear(colors["Blueberry"][0], colors["Non-Photo Blue"][0], HEIGHT - grass_height)))
g = list(map(int, linear(colors["Blueberry"][1], colors["Non-Photo Blue"][1], HEIGHT - grass_height)))
b = list(map(int, linear(colors["Blueberry"][2], colors["Non-Photo Blue"][2], HEIGHT - grass_height)))

for i in range(HEIGHT - grass_height):
    turtle.goto(-WIDTH / 2, HEIGHT / 2 - i)
    turtle.setheading(0)
    turtle.pencolor(r[i], g[i], b[i])
    turtle.pendown()
    turtle.forward(WIDTH)
    turtle.penup()

# grass
r = list(map(int, linear(colors["Green Lizard"][0], colors["Royal Green"][0], grass_height)))
g = list(map(int, linear(colors["Green Lizard"][1], colors["Royal Green"][1], grass_height)))
b = list(map(int, linear(colors["Green Lizard"][2], colors["Royal Green"][2], grass_height)))
for i in range(grass_height):
    turtle.goto(-WIDTH / 2, -HEIGHT / 2 + grass_height - i)
    turtle.setheading(0)
    turtle.pencolor(r[i], g[i], b[i])
    turtle.pendown()
    turtle.forward(WIDTH)
    turtle.penup()

# rainbow
r = sin_down() + zero(255) + sin_up()
g = sin_up() + sin_down() + zero(255)
b = zero(255) + sin_up() + sin_down()
for i in range(255 * 3):
    if i >= 255 // 2 and i % 2 == 0:
        turtle.goto(i + 50, -HEIGHT / 2 + grass_height)
        turtle.setheading(90)
        turtle.pencolor(r[len(r) - i - 1], g[len(r) - i - 1], b[len(r) - i - 1])
        turtle.pendown()
        turtle.circle(i + 50, 180, 200)
        turtle.penup()

turtle.update()
turtle.mainloop()
