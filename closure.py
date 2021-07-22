''' 求任意一元二次函数的值 '''


# 过程式
def curve(x, a, b, c):
    return a*x*x + b*x + c


print("过程式：")
print("y = ", curve(5, a=0, b=1, c=0))
print("y = ", curve(6, a=0, b=1, c=0))
print("y = ", curve(5, a=1, b=0, c=0))
print("y = ", curve(6, a=1, b=0, c=0))


# 面向对象
class Curve():
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    def getY(self, x):
        return self.a*x*x + self.b*x + self.c


print("面向对象：")
curve_a0b1c0 = Curve(0, 1, 0)
curve_a1b0c0 = Curve(1, 0, 0)
print("y = ", curve_a0b1c0.getY(5))
print("y = ", curve_a0b1c0.getY(6))
print("y = ", curve_a1b0c0.getY(5))
print("y = ", curve_a1b0c0.getY(6))


# 函数式
def curve_conf(a, b, c):
    def curve(x):
        return a*x*x + b*x + c
    return curve


print("函数式：")
curve_a0b1c0 = curve_conf(0, 1, 0)
curve_a1b0c0 = curve_conf(1, 0, 0)
print("y = ", curve_a0b1c0(5))
print("y = ", curve_a0b1c0(6))
print("y = ", curve_a1b0c0(5))
print("y = ", curve_a1b0c0(6))
