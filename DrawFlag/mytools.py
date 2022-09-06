"""
Copyright (c) 2022.
FileName: mytools.py
Brief: 抽象出一些基本操作制成的辅助工具。
Author: 青羽
Blog: https://chen-qingyu.github.io
CreateDate: 2022.09.06
"""

import turtle
import math


def my_range(start: float, stop: float, step: float = 1) -> list[float, ...]:
    """
    range函数拓展版，支持range函数所有功能加上浮点数。

    :param start: start number
    :param stop: stop number
    :param step: step number
    :return: a list of floats
    """
    ls = []
    while (start < stop) if step > 0 else (start > stop):
        ls.append(start)
        start += step
    return ls


def init_environment(title: str, width: float, height: float) -> None:
    """
    初始化环境。

    :param title: 窗口标题
    :param width: 窗口宽度
    :param height: 窗口高度
    """
    # Initialize turtle heading: to the right (east), positive angles: counterclockwise
    turtle.mode("standard")
    # Accelerate the drawing
    turtle.tracer(2)
    # Initialize window title
    turtle.title(title)
    # Initialize window size
    turtle.setup(width, height)
    # Initialize back-grond color: light gray
    turtle.bgcolor("#F0F0F0")
    # Set the angle measurement units to radians, for convenience of mathematical calculation
    turtle.radians()
    # Hide the path
    turtle.penup()
    # Hide the turtle
    turtle.hideturtle()


def draw_rect(x: float, y: float, width: float, height: float, fillcolor: str, angle: float = 0) -> None:
    """
    画矩形。

    :param x: 左上角x坐标
    :param y: 左上角y坐标
    :param width: x方向宽度
    :param height: y方向高度
    :param fillcolor: 填充颜色
    :param angle: 偏转角度 (矩形水平线与x轴的夹角弧度)
    """
    turtle.goto(x, y)
    turtle.fillcolor(fillcolor)
    turtle.begin_fill()
    for i in range(4):
        turtle.setheading(angle + i * -math.pi / 2)
        turtle.forward(width if i % 2 == 0 else height)
    turtle.end_fill()


def draw_star(x: float, y: float, radius: float, fillcolor: str, angle: float = 0) -> None:
    """
    画五角星。

    :param x: 五角星外接圆圆心x坐标
    :param y: 五角星外接圆圆心y坐标
    :param radius: 五角星外接圆半径
    :param fillcolor: 填充颜色
    :param angle: 偏转角度 (五角星上顶点到中心的连线与y轴的夹角弧度)
    """
    turtle.goto(x - radius * math.sin(angle), y + radius * math.cos(angle))
    turtle.fillcolor(fillcolor)
    turtle.begin_fill()
    for i in range(5):
        turtle.setheading(-2 * math.pi / 5 * (1 + 2 * i) + angle)
        turtle.forward(radius * math.cos(math.pi / 10) * 2)
    turtle.end_fill()


def draw_circle(x: float, y: float, radius: float, fillcolor: str, extent: tuple[float, float] = (0, 2 * math.pi),
                steps: int = None) -> None:
    """
    画圆。

    :param x: 圆心x坐标
    :param y: 圆心y坐标
    :param radius: 圆半径
    :param fillcolor: 填充颜色
    :param extent: 圆弧弧度
    :param steps: 分辨率
    """
    turtle.goto(x + radius, y)
    turtle.setheading(math.pi / 2)
    turtle.circle(radius, extent[0])
    turtle.fillcolor(fillcolor)
    turtle.begin_fill()
    turtle.circle(radius, extent[1] - extent[0], steps)
    turtle.end_fill()
