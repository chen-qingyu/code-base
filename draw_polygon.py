import turtle


def draw(sides: int):
    for i in range(18):
        for j in range(sides):
            turtle.forward(360 / sides)
            turtle.right(360 / sides)
        turtle.right(20)


if __name__ == '__main__':
    sides = eval(input("Please input the sides (2-36): "))
    while sides < 2 or sides > 36:
        sides = eval(input("Please input the sides (2-36): "))
    turtle.bgcolor("black")
    turtle.pencolor("white")
    turtle.hideturtle()
    turtle.tracer(2)
    draw(sides)
    turtle.penup()
    turtle.goto(0, -200)
    turtle.pendown()
    turtle.write('@ 青羽', font=("楷体", 16, "normal"))
    turtle.done()
