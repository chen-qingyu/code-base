l = [1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0]  # index: 0-12, total 13

# generate index list
ll = [0] + [i for i in range(1, len(l)) if l[i-1] != l[i]] + [len(l)]

# print result
for i in range(1, len(ll)):
    print(f"{'1' if i%2==l[0] else '0'}: [{ll[i-1]}, {ll[i]-1}]")
