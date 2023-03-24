from PIL import Image
import argparse


def preprocess(img_path, scale=20):
    img = Image.open(img_path)
    img = img.convert("RGB")  # 转为RGB格式
    width, height = img.size[0] // scale, img.size[1] // (2 * scale)  # 缩放倍数
    img = img.resize((width, height))
    return img


def rgb_to_char(r, g, b):
    # 映射字符串
    char_maping = 'MND8OZ$7I?+=~:,. '
    gray = int(0.2126 * r + 0.7152 * g + 0.0722 * b)
    unit = 256 / len(char_maping)
    return char_maping[int(gray / unit)]


def img_to_str(img, save_path):
    width, height = img.size
    txt = ''

    # 获取像素点的RGB元组值，并将其转化为字符
    for i in range(height):
        line = ''
        for j in range(width):
            line += rgb_to_char(*img.getpixel((j, i)))
        txt += line + '\n'

    # 保存字符画
    with open(save_path, 'w', encoding='utf-8') as f:
        f.write(txt)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert any image to ascii text.")
    parser.add_argument("file", type=str, help="input image file")
    args = parser.parse_args()

    img_path = args.file
    save_path = img_path + ".ascii.txt"
    img_to_str(preprocess(img_path), save_path)
