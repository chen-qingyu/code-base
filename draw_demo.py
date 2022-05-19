import turtle
import math


def draw_line(start: tuple[float, float], end: tuple[float, float]) -> None:
    turtle.penup()
    turtle.goto(start)
    turtle.pendown()
    turtle.goto(end)
    turtle.penup()


def draw_polygon(points: list[tuple[float, float], ...]) -> None:
    for i in range(1, len(points)):
        draw_line(points[i - 1], points[i])
    draw_line(points[-1], points[0])


def draw_star(edge: float = 100, center: tuple[float, float] = (0, 0)) -> None:
    turtle.penup()
    turtle.goto(center[0] - edge / 2, center[1] + (edge / 2 * math.tan(math.radians(18))))
    turtle.setheading(0)
    turtle.pendown()
    for i in range(5):
        turtle.forward(edge)
        turtle.right(144)
    turtle.penup()


def draw_snowflake(edge: float = 100, level: int = 2, center: tuple[float, float] = (0, 0)) -> None:
    def draw_koch(edge: float, level: int) -> None:
        if level == 0:
            turtle.forward(edge)
        else:
            for angle in [0, 60, -120, 60]:
                turtle.left(angle)
                draw_koch(edge / 3, level - 1)

    turtle.penup()
    turtle.goto(center[0] - edge / 2, center[1] + edge / 2 * math.tan(math.radians(30)))
    turtle.setheading(0)
    turtle.pendown()
    for i in range(3):
        draw_koch(edge, level)
        turtle.right(120)
    turtle.penup()


def draw_circle(radius: float = 50, center: tuple[float, float] = (0, 0)) -> None:
    turtle.penup()
    turtle.goto(center[0], center[1] - radius)
    turtle.setheading(0)
    turtle.pendown()
    turtle.circle(radius)
    turtle.penup()


if __name__ == '__main__':
    turtle.speed("fastest")
    turtle.bgcolor("white")

    turtle.color("cyan", "cyan")
    turtle.begin_fill()
    points1 = [(-150, 150), (150, 150), (150, -150), (-150, -150)]
    draw_polygon(points1)
    turtle.end_fill()

    turtle.color("green", "green")
    turtle.begin_fill()
    points2 = [(0, 200), (150, -150), (-150, -150)]
    draw_polygon(points2)
    turtle.end_fill()

    turtle.color("yellow", "yellow")
    turtle.begin_fill()
    draw_snowflake(250)
    turtle.end_fill()

    turtle.color("orange", "orange")
    turtle.begin_fill()
    draw_circle(105)
    turtle.end_fill()

    turtle.color("red", "red")
    turtle.begin_fill()
    draw_star(200)
    turtle.end_fill()

    turtle.hideturtle()
    turtle.mainloop()
