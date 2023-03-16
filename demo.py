''' 进制格式化输出 '''
# print("bin:{:6b},{:6b},{:6b},{:6b}".format(2, 4, 8, 16))
# print("oct:{:6o},{:6o},{:6o},{:6o}".format(2, 4, 8, 16))
# print("dec:{:6d},{:6d},{:6d},{:6d}".format(2, 4, 8, 16))
# print("hex:{:6x},{:6x},{:6x},{:6x}".format(2, 4, 8, 16))


''' * 与 ** 参数 '''
# def test_tuple(*args):
#     # *args 代表一个元组类型，是位置参数
#     print(args)
#     result = 0
#     for arg in args:
#         result += arg
#     return result

# def test_dict(**kwargs):
#     # **kwargs 代表一个字典类型，是默认参数
#     print(kwargs)
#     result = ""
#     for arg in kwargs:
#         result += arg
#     return result

# print(test_tuple(1, 2, 3, 4))
# print(test_dict(m=1, n=2))


''' Unicode码 '''
# print(list(map(ord, list("0123456789\0abcd\0编程喵(●'◡'●)"))))


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


''' 参数类型声明 '''
# def f(*x: int):
#     print(x)
# f(1, 2, 3)

# def g(x: tuple[int, ...]):
#     print(x)
# g((1, 2, 3))

# def h(x: list[int, any, ...]):
#     print(x)
# h([1, "1", 1.0])


''' switch '''
# status = 400
# match status:
#     case 400:
#         print("Bad request")
#     case 404:
#         print("Not found")
#     case 418:
#         print("I'm a teapot")
#     case _:
#         print("Something's wrong with the internet")


''' 从Haskell得到的灵感 '''
# # In Haskell: [2^n | n <- [0 .. 20], 2^n > 1000]
# [2**n for n in range(21) if 2**n > 1000]
# # return [1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576]

# # In Haskell: fac n = product [1 .. n]
# def fac(n): return 1 if n == 0 else n * fac(n - 1)
# # fac(500) is OK
