import numpy as np


def cycle_conv(x1, x2):
    # 确定循环卷积序列的长度N
    N = max(len(x1), len(x2))

    # 补0，让两个序列长度一致
    if len(x1) > len(x2):
        for i in range(len(x2), len(x1)):
            x2.append(0)
    elif len(x1) < len(x2):
        for i in range(len(x1), len(x2)):
            x1.append(0)

    # 序列x1周期延拓，以y轴为对称轴对称变换，截取0~N-1的序列
    temp_x1 = []
    temp_x1.append(x1[0])
    for i in range(1, len(x1)):
        temp_x1.append(x1[N-i])

    # 对周期延拓后的x1进行0~N-1的循环移动，计算得到一个N*N的cycle_matrix矩阵
    x1 = temp_x1
    cycle_matrix = []
    cycle_matrix.append(x1)
    for step in range(1, N):
        temp = []
        for i in range(0, N):
            temp.append(0)
        for i in range(0, N):
            temp[(i+step) % N] = x1[i]
        cycle_matrix.append(temp)

    cycle_matrix = np.array(cycle_matrix)
    # print(cycle_matrix)

    # 矩阵相乘得到循环卷积结果序列result
    result = np.matmul(cycle_matrix, np.transpose(x2))
    return result


def main():
    x1 = [1, 2, 3, 4]
    x2 = [1, 1, 1, 1, 0, 0, 0, 0]
    y = cycle_conv(x1, x2)
    print(y)


if __name__ == '__main__':
    main()
