''' 进制格式化输出 '''
# print("bin:{:6b},{:6b},{:6b},{:6b}".format(2, 4, 8, 16))
# print("oct:{:6o},{:6o},{:6o},{:6o}".format(2, 4, 8, 16))
# print("dec:{:6d},{:6d},{:6d},{:6d}".format(2, 4, 8, 16))
# print("hex:{:6x},{:6x},{:6x},{:6x}".format(2, 4, 8, 16))

''' 序列倒序 '''
# ch = "I LOVE YOU"
# ls = [0, 1, 2, 3]
# st = (0, 1, 2, 3)
# print(ch[::-1])
# print(ls[::-1])
# print(st[::-1])

''' * 与 ** 参数 '''
# def testTuple(*args):
#     # *args 代表一个元组类型，是位置参数
#     result = 0
#     for arg in args:
#         result += arg
#     print(args)
#     return result
# def testDict(**kwargs):
#     # **kwargs 代表一个字典类型，是默认参数
#     result = ""
#     for arg in kwargs:
#         result += arg
#     print(kwargs)
#     return result
# print(testTuple(1, 2, 3, 4))
# print(testDict(m=1, n=2))

''' this库 '''
# import this

''' keyword库 '''
# import keyword
# print(keyword.kwlist)
# print(len(keyword.kwlist))

''' dis库 '''
# import dis
# def foo(a, b):
#     return a + b
# dis.dis(foo)

''' os库 '''
# import os
# print(os.getcwd())
# print(os.cpu_count())
# print(os.getlogin())
# print(os.urandom(10))
# print(os.system("echo Hello World!"))

''' Unicode码 '''
# ch = "0123456789\x00abcd\x00编程喵\x00(●'◡'●)"
# print(list(map(ord, list(ch))))

''' 皮卡丘~ '''
# print("""
# 　　 へ　　　　　／|
# 　　/＼7　　　 ∠＿/
# 　 /　│　　 ／　／
# 　│　Z ＿,＜　／　　 /`ヽ
# 　│　　　　　ヽ　　 /　　〉
# 　 Y　　　　　`　 /　　/
# 　ｲ●　､　●　　⊂⊃〈　　/
# 　()　 へ　　　　|　＼〈
# 　　>ｰ ､_　 ィ　 │ ／／
# 　 / へ　　 /　ﾉ＜| ＼＼
# 　 ヽ_ﾉ　　(_／　 │／／
# 　　7　　　　　　　|／
# 　　＞―r￣￣`ｰ―＿　
# """)

''' 列表生成式 '''
# print([x * x for x in range(10) if x % 2])
# d = {'Adam': 95, 'Lisa': 89, 'Bill': 60}
# table = ["<tr><td>%s</td><td>%s</td></tr>" % (name, score) for name, score in d.items()]
# with open("out.html", "w") as fo:
#     fo.write('<table border="1"><tr><th>name</th><th>score</th></tr>' + "\n".join(table) + "</table>")

''' switch '''
# case = input("Please input a case: ")
# switch = {'1': 'case 1', '2': 'case 2', '3': 'case 3', '4': 'case 4'}
# print(switch.get(case,'Invalid input'))

''' 提取每一位数字 '''
# print(list(map(eval, list(str(2333)))))

''' 数字范围映射 '''
# def num_map(x, x_min, x_max, y_min, y_max):
#     slope = (y_max - y_min) / (x_max - x_min)
#     return y_min + round(slope * (x - x_min))


# print(num_map(5, 0, 10, 0, 100))  # => 50
# print(num_map(128, 0, 256, 0, 1024))  # => 512
