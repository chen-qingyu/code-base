from turtle import *

WriteStep = 15
Width = 600
Height = 600
Xh = 0
Yh = 0


def bezier(p1, p2, t):
    return p1 * (1 - t) + p2 * t


def bezier_2(x1, y1, x2, y2, x3, y3, x4, y4):
    x1 = -Width / 2 + x1
    y1 = Height / 2 - y1
    x2 = -Width / 2 + x2
    y2 = Height / 2 - y2
    x3 = -Width / 2 + x3
    y3 = Height / 2 - y3
    x4 = -Width / 2 + x4
    y4 = Height / 2 - y4
    goto(x1, y1)
    pendown()
    for t in range(0, WriteStep + 1):
        x = bezier(bezier(bezier(x1, x2, t / WriteStep),
                          bezier(x2, x3, t / WriteStep), t / WriteStep),
                   bezier(bezier(x2, x3, t / WriteStep),
                          bezier(x3, x4, t / WriteStep), t / WriteStep), t / WriteStep)
        y = bezier(bezier(bezier(y1, y2, t / WriteStep),
                          bezier(y2, y3, t / WriteStep), t / WriteStep),
                   bezier(bezier(y2, y3, t / WriteStep),
                          bezier(y3, y4, t / WriteStep), t / WriteStep), t / WriteStep)
        goto(x, y)
    penup()


def moveto(x, y):  # 移动到svg坐标下（x，y）
    penup()
    goto(-Width / 2 + x, Height / 2 - y)


def line(x1, y1, x2, y2):  # 连接svg坐标下两点
    penup()
    goto(-Width / 2 + x1, Height / 2 - y1)
    pendown()
    goto(-Width / 2 + x2, Height / 2 - y2)
    penup()


def lineto(dx, dy):  # 连接当前点和相对坐标（dx，dy）的点
    pendown()
    goto(xcor() + dx, ycor() - dy)
    penup()


def lineto_svg(x, y):  # 连接当前点和svg坐标下（x，y）
    pendown()
    goto(-Width / 2 + x, Height / 2 - y)
    penup()


def horizontal_svg(x):  # 做到svg坐标下横坐标为x的水平线
    pendown()
    setx(x - Width / 2)
    penup()


def horizontal(dx):  # 做到相对横坐标为dx的水平线
    seth(0)
    pendown()
    fd(dx)
    penup()


def vertical(dy):  # 做到相对纵坐标为dy的垂直线
    seth(-90)
    pendown()
    fd(dy)
    penup()
    seth(0)


def polyline(x1, y1, x2, y2, x3, y3):  # 做svg坐标下的折线
    penup()
    goto(-Width / 2 + x1, Height / 2 - y1)
    pendown()
    goto(-Width / 2 + x2, Height / 2 - y2)
    goto(-Width / 2 + x3, Height / 2 - y3)
    penup()


def curveto(x1, y1, x2, y2, x, y):  # 三阶贝塞尔曲线到（x，y）
    penup()
    x_now = xcor() + Width / 2
    y_now = Height / 2 - ycor()
    bezier_2(x_now, y_now, x1, y1, x2, y2, x, y)
    global Xh
    global Yh
    Xh = x - x2
    Yh = y - y2


def curveto_r(x1, y1, x2, y2, x, y):  # 三阶贝塞尔曲线到相对坐标（x，y）
    penup()
    x_now = xcor() + Width / 2
    y_now = Height / 2 - ycor()
    bezier_2(x_now, y_now, x_now + x1, y_now + y1,
             x_now + x2, y_now + y2, x_now + x, y_now + y)
    global Xh
    global Yh
    Xh = x - x2
    Yh = y - y2


def smooth(x2, y2, x, y):  # 平滑三阶贝塞尔曲线到（x，y）
    global Xh
    global Yh
    penup()
    x_now = xcor() + Width / 2
    y_now = Height / 2 - ycor()
    bezier_2(x_now, y_now, x_now + Xh, y_now + Yh, x2, y2, x, y)
    Xh = x - x2
    Yh = y - y2


def smooth_r(x2, y2, x, y):  # 平滑三阶贝塞尔曲线到相对坐标（x，y）
    global Xh
    global Yh
    penup()
    x_now = xcor() + Width / 2
    y_now = Height / 2 - ycor()
    bezier_2(x_now, y_now, x_now + Xh, y_now + Yh,
             x_now + x2, y_now + y2, x_now + x, y_now + y)
    Xh = x - x2
    Yh = y - y2


tracer(2)
pensize(1)
penup()

# 图层_2
color("black", "#F2F2F2")  # 外套
moveto(61, 462)
begin_fill()
smooth_r(12, -41, 27, -58)
curveto_r(-6, -36, 6, -118, 9, -132)
curveto_r(-15, -27, -23, -51, -26, -74)
curveto_r(4, -66, 38, -105, 65, -149)
horizontal_svg(486)
curveto_r(12, 24, 40, 99, 33, 114)
curveto_r(39, 82, 55, 129, 39, 144)
smooth_r(-31, 23, -39, 28)
smooth_r(-12, 37, -12, 37)
lineto(50, 92)
horizontal_svg(445)
smooth_r(-29, -38, -31, -46)
smooth_r(78, -107, 72, -119)
smooth(355, 178, 340, 176)
smooth(272, 63, 264, 64)
smooth_r(-29, 67, -27, 73)
curveto(99, 292, 174, 428, 173, 439)
smooth_r(-8, 23, -8, 23)
lineto_svg(61, 462)
end_fill()

moveto(60.5, 461.5)  # 阴影
color("black", "#D3DFF0")
begin_fill()
curveto_r(0, 0, 17, -42, 27, -59)
curveto_r(-6, -33, 6, -128, 10, -133)
curveto_r(-15, -10, -27, -66, -27.285, -75)
pencolor("#D3DFF0")
curveto_r(12.285, 11, 82.963, 156, 82.963, 156)
pencolor("black")
smooth_r(12.322, 75, 19.322, 86)
curveto_r(-1, 11, -8, 25, -8, 25)
horizontal_svg(60.5)
end_fill()

moveto(444.5, 464)
begin_fill()
curveto_r(0, 0, -29, -36, -31, -46)
smooth_r(53.59, -82.337, 53.59, -82.337)
pencolor("#D3DFF0")
smooth_r(86.41, -47.663, 96.072, -54.85)
curveto(563.5, 297.5, 570.5, 299.5, 518.5, 334)
pencolor("black")
curveto_r(-2, 16, -12, 33, -12, 37)
smooth_r(50, 92, 50, 93)
horizontal_svg(444.5)
end_fill()

moveto(195, 50)
begin_fill()
pencolor("#D3DFF0")
polyline(195, 50, 175.5, 106.5, 202.522, 50)
horizontal_svg(195)
end_fill()

moveto(327.997, 49)
begin_fill()
curveto_r(0, 0, 11.503, 121.087, 13.503, 128.087)
curveto_r(11, 2, 54, 37, 54, 37)
lineto(-40, -164)
horizontal_svg(327.997)
end_fill()

moveto(94.5, 397.5)
pencolor("black")
line(94.5, 397.5, 107.5, 373.5)  # 皱纹
line(122.5, 317.5, 95.875, 274.699)
line(122.5, 341.5, 141.5, 402.5)
line(141.5, 409.5, 153.5, 431.5)
line(340.023, 49, 360.5, 144)
line(478.5, 95.5, 518.5, 161.5)
line(518.5, 332.5, 460.5, 359.5)
polyline(506.5, 369.5, 493.5, 402.5, 502.5, 443.5)
moveto(530, 429)
curveto_r(4, 16, -5, 33, -5, 33)

# 图层_3
color("black", "#2b1d2a")  # 外套内侧
moveto(225, 462)
begin_fill()
horizontal_svg(165)
smooth_r(9, -15, 8, -25)
curveto_r(-47, -126, 6, -212, 12, -225)
curveto(185, 305, 202, 428, 225, 462)
lineto_svg(225, 462)
end_fill()

moveto(390, 462)
begin_fill()
curveto_r(10, -23, 34, -180, 35, -222)
curveto_r(7, 4, 54, 45, 61, 61)
smooth_r(-73, 101, -72, 118)
curveto_r(5, 15, 31, 46, 31, 45)
lineto_svg(390, 462)
end_fill()

# 图层_4
color("black", "#2b1d29")  # 外套内侧
moveto(225, 462)
begin_fill()
curveto_r(-28, -50, -40, -166, -40, -250)
curveto_r(6, 51, -6, 87, 45, 106)
smooth_r(64, 27, 89, 24)
smooth_r(49, -18, 56, -20)
smooth_r(50, -10, 51, -85)
curveto_r(0, 29, -25, 201, -36, 225)
lineto_svg(225, 462)
end_fill()

# 图层_5
color("black", "#3D3D3D")  # 衣服
moveto(225, 462)
begin_fill()
curveto_r(-5, -5, -22, -53, -23, -70)
lineto(32, -13)
curveto_r(3, -25, 6, -28, 12, -36)
smooth_r(13, -12, 16, -12)
vertical(-2)
curveto_r(45, 20, 64, 14, 94, 1)
vertical(2)
curveto_r(8, -2, 15, 2, 17, 4)
smooth_r(0, 6, -2, 9)
curveto_r(10, 10, 10, 29, 11, 33)
smooth_r(23, 4, 25, 6)
smooth_r(-17, 83, -17, 78)
lineto_svg(225, 462)
end_fill()

# 图层_6
color("black", "#968281")  # 脖子
moveto(262, 329)
begin_fill()
vertical(17)
curveto_r(1, 2, 44, 14, 45, 15)
smooth_r(3, 12, 3, 12)
horizontal(3)
vertical(-5)
curveto_r(1, -3, 4, -6, 5, -7)
lineto(36, -14)
curveto_r(1, -1, 3, -16, 2, -17)
curveto(318, 348, 296, 344, 262, 329)
end_fill()

# 图层_7
color("black", "#A2B8D6")  # 衣领
moveto(262, 331)
begin_fill()
curveto_r(0, 8, -1, 13, 0, 15)
smooth_r(43, 14, 45, 15)
lineto(3, 12)
horizontal(3)
smooth_r(-1, -3, 0, -5)
lineto(5, -7)
lineto(36, -14)
curveto_r(1, -1, 2, -12, 2, -15)
smooth_r(25, -2, 15, 13)
curveto_r(-2, 4, -7, 29, -7, 32)
smooth_r(-35, 19, -41, 22)
smooth_r(-9, 14, -12, 14)
smooth_r(-7, -12, -14, -15)
curveto_r(-19, -2, -41, -25, -41, -25)
smooth_r(-10, -26, -10, -30)
smooth(255, 332, 262, 331)
end_fill()

moveto(262, 346)
lineto(-12, -6)
moveto(369, 333)
curveto_r(2, 4, -6, 10, -15, 14)

# 图层_8
color("black", "#E7F1FF")  # 白色褶皱
moveto(225, 462)
begin_fill()
lineto(-3, -5)
curveto_r(0, -2, 4, -4, 5, -6)
smooth_r(16, 3, 19, -8)
smooth_r(0, -7, 0, -11)
smooth_r(5, -8, 9, -5)
smooth_r(19, -8, 19, -11)
smooth_r(6, -7, 6, -7)
smooth_r(7, -2, 9, -4)
lineto(41, -2)
lineto(12, 9)
smooth_r(3, 15, 7, 18)
smooth_r(15, 4, 17, 4)
smooth_r(4, -4, 6, -4)
smooth_r(6, 4, 5, 9)
smooth_r(0, 9, 0, 9)
smooth_r(1, 7, 7, 6)
smooth_r(8, 0, 8, 0)
lineto(-2, 8)
lineto_svg(225, 462)
end_fill()

pensize(2)
moveto(240, 450)
smooth_r(0, 9, 3, 12)
moveto(372, 462)
curveto_r(-2, -4, -5, -29, -7, -28)
pensize(1)

# 图层_9
color("black", "#151515")  # 领结
moveto(247, 358)
begin_fill()
curveto_r(-5, 3, -8, 20, -6, 23)
curveto_r(25, 21, 50, 17, 50, 17)
lineto(-23, 64)
horizontal(22)
smooth_r(1, -13, 2, -16)
lineto(13, -50)
curveto_r(2, 2, 7, 3, 10, 1)
smooth_r(18, 65, 18, 65)
horizontal(19)
lineto(-24, -65)
curveto_r(21, 5, 39, -10, 44, -13)
curveto_r(5, -20, 1, -21, 0, -24)
curveto_r(-18, -2, -49, 15, -52, 17)
smooth_r(-11, -3, -15, -1)
smooth(252, 356, 247, 358)
end_fill()

# 图层_10
color("black", "#A2B8D6")  # 衣领（透过领结）
moveto(297, 387)
begin_fill()
lineto(-11, 6)
curveto_r(-1, 0, -20, -7, -30, -19)
curveto(259, 373, 297, 385, 297, 387)
end_fill()

moveto(323, 384)
begin_fill()
lineto(8, 7)
lineto(30, -14)
curveto_r(1, -1, 5, -6, 4, -7)
smooth(329, 379, 323, 384)
end_fill()

# 图层_11
color("black", "#F3EEEB")  # 脸
moveto(185, 212)
begin_fill()
curveto_r(4, -9, 46, -77, 52, -75)
curveto_r(-2, -17, 19, -68, 27, -73)
curveto_r(16, 15, 71, 108, 76, 112)
smooth_r(76, 53, 86, 60)
curveto_r(0, 65, -27, 75, -31, 76)
curveto_r(-50, 28, -70, 30, -85, 30)
smooth_r(-77, -22, -86, -26)
curveto(180, 302, 186, 228, 185, 212)
end_fill()

# 图层_12
color("black", "#2B1D29")  # 头发
moveto(189, 202)
begin_fill()
curveto_r(-1, 22, 19, 51, 19, 51)
smooth_r(-10, -42, 7, -92)
curveto(212, 168, 196, 189, 189, 202)
end_fill()

moveto(221, 155)
begin_fill()
curveto_r(-2, 6, 5, 48, 5, 48)
smooth_r(18, -28, 20, -48)
curveto_r(-5, 24, 4, 43, 7, 50)
curveto_r(-10, -49, 3, -72, 13, -106)
curveto_r(-2, -7, -3, -32, -3, -35)
curveto_r(-17, 18, -27, 71, -27, 71)
lineto_svg(221, 155)
end_fill()

moveto(264, 64)
begin_fill()
curveto_r(-4, 5, 14, 100, 14, 100)
smooth_r(-6, -79, -5, -85)
curveto_r(0, 98, 49, 139, 49, 139)
smooth_r(8, -50, 3, -65)
smooth(272, 64, 264, 64)
end_fill()

moveto(342, 176)
begin_fill()
curveto_r(-1, 27, -10, 57, -10, 57)
smooth_r(20, -33, 17, -54)
lineto_svg(342, 176)
end_fill()

penup()
begin_fill()
polyline(349, 180, 353, 203, 361, 203)
polyline(361, 203, 362, 188, 349, 180)
end_fill()

# 图层_13
pensize(2)
moveto(210, 180)  # 眉毛
curveto_r(5, -4, 63, 9, 63, 14)
moveto(338, 193)
curveto_r(0, -3, 18, -6, 18, -6)
pensize(1)

# 图层_14
color("black", "#D1D1D1")  # 眼睛1
pensize(2)
moveto(206, 212)
begin_fill()
lineto(15, -7)
curveto_r(4, -1, 26, -2, 30, 0)
smooth_r(10, 3, 12, 7)
pencolor("#D1D1D1")
pensize(1)
smooth_r(2, 27, -1, 30)
smooth_r(-39, 5, -44, 1)
smooth(206, 212, 206, 212)
end_fill()

moveto(384, 204)
begin_fill()
pencolor("black")
pensize(2)
curveto_r(-3, -1, -18, -1, -28, 1)
smooth_r(-9, 6, -10, 9)
pencolor("#D1D1D1")
pensize(1)
smooth_r(3, 18, 6, 23)
smooth_r(38, 6, 40, 4)
smooth_r(10, -9, 13, -22)
pencolor("black")
pensize(2)
lineto_svg(384, 204)
end_fill()

# 图层_15
color("#0C1631", "#0C1631")  # 眼睛2
pensize(1)
moveto(216, 206)
begin_fill()
curveto_r(-1, 5, 0, 26, 7, 35)
smooth_r(30, 2, 33, 0)
smooth_r(5, -31, 2, -34)
smooth(219, 203, 216, 206)
end_fill()

moveto(354, 207)
begin_fill()
curveto_r(-2, 1, 2, 29, 4, 31)
smooth_r(30, 3, 33, 1)
smooth_r(6, -24, 4, -27)
lineto(-11, -8)
curveto(382, 204, 357, 206, 354, 207)
end_fill()

# 图层_16
pencolor("black")  # 眼睛(线条)
pensize(3)
moveto(225, 215)
curveto_r(10, 28, 22, 16, 24, 6)
moveto(365, 219)
curveto_r(4, 14, 18, 24, 22, -3)
pensize(2)
line(240.5, 207.5, 227.5, 211.5)
line(245.5, 209.5, 227.5, 214.5)
line(247.5, 211.5, 227.5, 217.5)
line(247.5, 214.5, 229.5, 220.5)
line(247.5, 218.5, 230.5, 223.5)
line(246.5, 222.5, 232.5, 226.5)
line(244.5, 225.5, 234.5, 228.5)
line(377.5, 207.5, 367.5, 210.5)
line(384.5, 207.5, 366.5, 212.5)
line(385.5, 210.5, 366.5, 215.5)
line(384.5, 213.5, 366.5, 218.5)
line(384.5, 215.5, 367.5, 220.5)
line(384.5, 218.5, 368.5, 223.5)
line(382.5, 223.5, 370.5, 227.5)

# 图层_17
color("#F5F5F5", "#F5F5F5")  # 眼睛3
moveto(253, 211)
begin_fill()
curveto_r(-3, 0, -8, 8, 1, 10)
smooth(258, 210, 253, 211)
end_fill()

moveto(392, 209)
begin_fill()
lineto(4, 3)
vertical(4)
lineto(-4, 2)
curveto(386, 214, 392, 209, 392, 209)
end_fill()

# 图层_18
color("#352F53", "#352F53")  # 眼睛4
moveto(219, 229)
begin_fill()
smooth_r(2, -5, 6, -4)
smooth_r(18, 13, 27, 1)
curveto_r(3, 0, 5, 3, 5, 3)
vertical(13)
horizontal_svg(224)
lineto_svg(219, 229)
end_fill()

moveto(357, 227)
begin_fill()
smooth_r(4, -6, 10, -2)
smooth_r(10, 13, 19, 1)
curveto_r(6, 0, 8, 6, 8, 6)
lineto(-2, 9)
curveto_r(-12, 3, -29, 0, -32, -2)
smooth(357, 227, 357, 227)
end_fill()

# 图层_19
color("#9A90CB", "#9A90CB")  # 眼睛5
moveto(227, 231)
begin_fill()
curveto_r(-6, 0, -5, 5, -3, 8)
smooth_r(24, 2, 27, 0)
smooth_r(0, -8, -1, -8)
smooth(234, 231, 227, 231)
end_fill()

moveto(361, 227)
begin_fill()
curveto_r(2, 18, 26, 14, 30, 6)
smooth_r(-1, -3, -2, -4)
smooth_r(-15, 9, -24, -4)
curveto(363, 224, 361, 225, 361, 227)
end_fill()

# 图层_20
pencolor("black")
moveto(309, 270)  # 鼻子、嘴
curveto_r(0, 0, 4, 7, 1, 9)
line(296.5, 307.5, 303.5, 307.5)
moveto(315, 307)
smooth_r(10, -1, 10, 2)

penup()
hideturtle()
update()
done()
