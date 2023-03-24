def P(n, N):
    # n个盒子，N个球，n>N，求每个盒子最多有一个球的概率。古典概型分球入杯问题
    product = 1
    for i in range(n, n - N, -1):
        product *= i
    return product / (n ** N)


number = 50
print("班上{}个同学正好有两个同学生日在同一天的概率：{:.2%}".format(number, 1 - P(365, number)))
