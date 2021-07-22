from random import *


def printIntro():
    print("这个程序模拟两个选手A和B的某种比赛")
    print("程序运行需要A和B的能力值（0-1之间）")
    print("================================")


def getInputs():
    a = eval(input("请输入选手A的能力值（0-1）："))
    b = eval(input("请输入选手B的能力值（0-1）："))
    n = eval(input("请输入模拟比赛的场次："))
    print("================================")
    return a, b, n


def simOneGame(A, B):
    scoreA, scoreB = 0, 0
    begin = "A"
    while scoreA != 15 and scoreB != 15:
        if begin == "A":
            if random() < A:
                scoreA += 1
            else:
                begin = "B"
        else:
            if random() < B:
                scoreB += 1
            else:
                begin = "A"
    return scoreA, scoreB


def simNGames(A, B, n):
    winA, winB = 0, 0
    for i in range(n):
        scoreA, scoreB = simOneGame(A, B)
        if scoreA > scoreB:
            winA += 1
        else:
            winB += 1
    return winA, winB


def printSummary(winA, winB):
    n = winA + winB
    print("竞技分析开始，共分析{}场比赛".format(n))
    print("选手A获胜{}场比赛，胜率{:.2%}".format(winA, winA / n))
    print("选手B获胜{}场比赛，胜率{:.2%}".format(winB, winB / n))


def main():
    try:
        printIntro()
        A, B, n = getInputs()
        assert 0 <= A <= 1 and 0 <= B <= 1, "能力值只能在0-1之间"
        winA, winB = simNGames(A, B, n)
        printSummary(winA, winB)
    except Exception as e:
        print("Error: %s" % e)
    input()


main()
