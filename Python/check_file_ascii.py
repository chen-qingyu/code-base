import sys
import os


def check_file_ascii(file):
    """
    检测文件中是否存在非ASCII字符，并输出包含非ASCII字符的行
    """
    non_ascii_lines = []

    try:
        with open(file, 'r', encoding='utf-8') as fo:
            for line_number, line in enumerate(fo, start=1):
                if not line.isascii():
                    non_ascii_lines.append((line_number, line.strip()))
    except FileNotFoundError:
        print(f"文件 {file} 未找到")
        return
    except Exception as e:
        print(f"读取文件 {file} 时发生错误：{e}")
        return

    if non_ascii_lines:
        print(f"文件 {file} 中包含非ASCII字符的行如下：")
        for line_number, line in non_ascii_lines:
            print(f"第 {line_number} 行：{line}")
    else:
        print(f"文件 {file} 中全是ASCII字符")


def check_folder_ascii(folder):
    """
    遍历指定目录中的所有文件，并检测每个文件中是否存在非ASCII字符
    """
    if not os.path.isdir(folder):
        print(f"路径 {folder} 不是一个有效的目录")
        return

    for root, dirs, files in os.walk(folder):
        for file in files:
            path = os.path.join(root, file)
            if '.git' in path or 'check_file_ascii.py' in path:
                continue
            print(f"正在检查文件：{path}")
            check_file_ascii(path)


if __name__ == '__main__':
    if len(sys.argv) == 2:
        check_folder_ascii(sys.argv[1])
    else:
        print("使用参数指定目录")
