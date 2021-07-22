import random


def OK(queen, nextX):
    nextY = len(queen)
    for i in range(nextY):
        if abs(queen[i] - nextX) in (0, nextY - i):
            return False  # 水平距离如果为零或者等于垂直距离则返回 False
    return True


def queens(num, queen=()):
    # ref: http://www.zhihu.com/question/32322577
    for pos in range(num):
        if OK(queen, pos):
            if len(queen) == num - 1:  # 如果只剩一个皇后没有放置
                yield (pos + 1,)
            # 否则，把当前皇后的位置信息，添加到状态列表里，并传递给下一皇后。
            # 程序要从前面的皇后得到包含位置信息的元组，并要为后面的皇后提供当前皇后的每一种合法的位置信息
            else:
                for result in queens(num, queen + (pos,)):
                    yield (pos + 1,) + result


def draw(solution):
    def line(pos, length=len(solution)):
        return '. ' * (pos - 1) + '$ ' + '. ' * (length - pos)
    for pos in solution:
        print(line(pos))


if __name__ == "__main__":
    draw(random.choice(list(queens(4))))
    for item in queens(4):
        print(item)
