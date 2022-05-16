class Point:
    """ operator overload demo """

    def __init__(self, x: int = 0, y: int = 0):
        self.x = x
        self.y = y

    def __str__(self):
        return "({},{})".format(self.x, self.y)

    def __eq__(self, other):
        return self.x == other.x or self.y == other.y

    def __ne__(self, other):
        return not self == other

    def __lt__(self, other):
        return (self.x ** 2 + self.y ** 2) < (other.x ** 2 + other.y ** 2)

    def __gt__(self, other):
        return (self.x ** 2 + self.y ** 2) > (other.x ** 2 + other.y ** 2)

    def __le__(self, other):
        return self < other or self == other

    def __ge__(self, other):
        return self > other or self == other

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)


p1 = Point()
p2 = Point(1, 1)
print(p1, p2)
print(p1 <= p2)
print(p1 >= p2)
print(p1 + p2)
print(p1 - p2)
print(p1, p2)


class Stream:
    """ C++ std cout """

    __instance = None

    def __new__(cls, *args, **kwargs):  # Implement singleton
        if not cls.__instance:
            cls.__instance = super().__new__(cls)
        return cls.__instance

    def __lshift__(self, other):
        print(other, end='')
        return self


cout = Stream()
cout2 = Stream()

cout << "Hello" << " " << "World" << "!" << '\n'
cout2 << "Python" << " " << "cout" << "~" << '\n'
print("cout is cout2:", cout is cout2)
