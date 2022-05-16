import turtle

turtle.tracer(100)
turtle.hideturtle()
turtle.colormode(255)
for i in range(255 // 5):
    turtle.color(5 * i, 1 * i, 3 * i)
    turtle.begin_fill()
    turtle.seth(130)
    turtle.fd(220)
    turtle.circle(-80, 230)
    turtle.seth(100)
    turtle.circle(-80, 230)
    turtle.fd(220)
    turtle.end_fill()
turtle.done()
