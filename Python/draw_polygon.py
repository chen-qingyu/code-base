import turtle


def draw(sides: int):
    for i in range(18):
        for j in range(sides):
            turtle.forward(360 / sides)
            turtle.right(360 / sides)
        turtle.right(20)


if __name__ == '__main__':
    sides = 0
    while sides < 2 or sides > 36:
        sides = int(input("Please input the sides (2-36): "))
    turtle.bgcolor("black")
    turtle.pencolor("white")
    turtle.hideturtle()
    turtle.tracer(2)
    draw(sides)
    turtle.done()
