import numpy as np
import matplotlib.pyplot as plt

SAMPLE_RATE = 2000  # 采样频率(Hz)


def main():
    # 从文本文件读取数据
    data = read_data("./data.txt")

    # 绘制数据的时域和频域图像
    plot_diagram(data)


def read_data(file):
    ''' 读取数据 '''

    data = []

    with open(file, encoding='utf8') as fo:
        # 读取文件的每一行
        lines = fo.readlines()
        for line in lines:
            # 处理得到采样数据
            data.append(float(line))

    return data


def calc_fft(data):
    ''' 计算频谱 '''

    # 采样长度
    length = len(data)

    # 根据采样率和采样长度生成时间序列
    t = np.linspace(0, length/SAMPLE_RATE, length)

    # 将采样数据转换成numpy的array格式
    xt = np.array(data)

    # 利用np.fft.rfft()进行FFT计算
    xf = np.fft.rfft(xt) / length

    # 根据采样率和采样长度计算出每个下标对应的真正频率
    freqs = np.linspace(0, SAMPLE_RATE/2, length//2+1)

    # 取绝对值表示幅值
    xfa = np.abs(xf)

    return (freqs, xfa)


def plot_diagram(data):
    ''' 绘制数据的时域和频域图像 '''

    length = len(data)
    t = np.linspace(0, length/SAMPLE_RATE, length)
    xt = np.array(data)

    (freqs, xfa) = calc_fft(data)

    # 作图
    plt.subplot(2, 1, 1)
    plt.title("Time Domain")
    plt.xlabel("Time (s)")
    plt.ylabel("A")
    plt.plot(t, xt)

    plt.subplot(2, 1, 2)
    plt.title("Freq Domain")
    plt.xlabel("Freq (Hz)")
    plt.ylabel('A')
    plt.plot(freqs[1:], xfa[1:])  # [1:]去掉f=0的直流信号

    plt.subplots_adjust(hspace=0.5)  # 拉宽上下子图距离，不然会挡住字
    plt.show()


if __name__ == "__main__":
    main()
