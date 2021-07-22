from turtle import *

screen = Screen()
pensize(20)
colormode(255)
speed(100)
for i in range(51):
    color(5 * i, 1 * i, 3 * i)
    begin_fill()
    seth(130)
    fd(220)
    circle(-80, 230)
    seth(100)
    circle(-80, 230)
    fd(220)
    end_fill()
hideturtle()
done()
