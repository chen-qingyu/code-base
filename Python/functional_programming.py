l = [1, 2, 3, 4, 5]
print(l)
print("---")


def my_map(f, l):
    if l == []:
        return []
    else:
        return [f(l[0])] + my_map(f, l[1:])


print(list(map(lambda x: x * x, l)))
print(list(my_map(lambda x: x * x, l)))
print("---")


def my_filter(p, l):
    if l == []:
        return []
    elif p(l[0]):
        return [l[0]] + my_filter(p, l[1:])
    else:
        return my_filter(p, l[1:])


print(list(filter(lambda x: x % 2 == 1, l)))
print(list(my_filter(lambda x: x % 2 == 1, l)))
print("---")


def my_len(l):
    if l == []:
        return 0
    else:
        return 1 + my_len(l[1:])


print(len(l))
print(my_len(l))
print("---")
