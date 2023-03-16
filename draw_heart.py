import turtle


def curve(degree):
    for i in range(degree):
        turtle.right(1)
        turtle.forward(1)


turtle.title("My heart")
turtle.tracer(2)
turtle.bgcolor("pink")
turtle.color("red")
turtle.pensize(2)
turtle.setup(800, 600)
turtle.hideturtle()

turtle.begin_fill()
turtle.left(140)
turtle.forward(111)
curve(200)
turtle.left(120)
curve(200)
turtle.forward(112)
turtle.end_fill()
turtle.done()
