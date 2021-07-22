# def Fibonacci(n):
#     # 指数时间复杂度
#     if n == 1 or n == 2:
#         return 1
#     else:
#         return Fibonacci(n - 1) + Fibonacci(n - 2)


def Fibonacci(n):
    t1 = 1
    t2 = 1
    if n > 2:
        for i in range(2, n):
            temp = t1 + t2
            t1 = t2
            t2 = temp
    return t2


while True:
    n = eval(input("Please enter a positive integer: "))
    if n < 1 or not isinstance(n, int):
        break

    fib = []
    for i in range(1, n + 1):
        fib.append(Fibonacci(i))

    print("The Fibonacci sequence is:", fib)
    print("The sum is:", sum(fib))
