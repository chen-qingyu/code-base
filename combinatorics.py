import itertools

# 笛卡尔积
for x in itertools.product('ABC'):
    print(x)

print("="*10)

# 排列
for x in itertools.permutations('ABC'):
    print(x)

print("="*10)

# 组合
for x in itertools.combinations('ABC', 2):
    print(x)

print("="*10)

# 可重复组合
for x in itertools.combinations_with_replacement('ABC', 2):
    print(x)

print("="*10)


# 组合数与2的幂

n = 12

# 组合数
arr1 = [0]*n
for i in range(n):
    arr1[i] = len(list(itertools.combinations(range(i*2), i)))
print(arr1)

# 2的幂
arr2 = [0]*n
for i in range(n):
    arr2[i] = 2**i
print(arr2)

for i in range(n):
    print(arr1[i]/arr2[i], end=" ")
