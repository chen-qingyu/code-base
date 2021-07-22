from PIL import Image

# 映射字符串
char_maping = 'MND8OZ$7I?+=~:,. '


def preprocess(imgPath, scale=20):
    img = Image.open(imgPath)
    img = img.convert("RGB")  # 转为RGB格式
    width, height = img.size
    width, height = width // scale, height // scale  # 缩放倍数
    img = img.resize((width, height))
    return img


def RGBToChar(r, g, b):
    length = len(char_maping)
    gray = int(0.2126 * r + 0.7152 * g + 0.0722 * b)
    unit = 256 / length
    idx = int(gray / unit)
    return char_maping[idx]


def imgToStr(img, savePath):
    width, height = img.size
    txt = ''

    # 获取像素点的RGB元组值，并将其转化为字符
    for i in range(height):
        line = ''
        for j in range(width):
            line += RGBToChar(*img.getpixel((j, i)))
        txt = txt + line + '\n'

    # 保存字符画
    with open(savePath, 'w', encoding='utf-8') as f:
        f.write(txt)


imgPath = './test.jpg'
savePath = './out.txt'
img = preprocess(imgPath)
imgToStr(img, savePath)
