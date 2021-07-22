from turtle import *


def curvemove():
    for i in range(200):
        right(1)
        forward(1)


speed(100)
window = Screen()
window.bgcolor("pink")
hideturtle()
color("red")
pensize(2)
begin_fill()
left(140)
forward(111)
curvemove()
left(120)
curvemove()
forward(111)
end_fill()
penup()
done()
