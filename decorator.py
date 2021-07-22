'''
独立写出来的计时装饰器：
- 可传任意参数
- 有返回值
- 命名规范
'''
import time


def timer(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        ret = func(*args, **kwargs)
        end = time.time()
        print("@timer: cost %.1f s." % (end - start))
        return ret
    return wrapper


@timer
def foo(x):
    print("foo's args: ", x)
    time.sleep(1)
    return "foo return."


# foo = timer(foo)

print(foo('233'))
