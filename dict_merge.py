dic1 = {"a": 1, "b": 2}
dic2 = {"a": 11, "c": 3}

dic = {}
for key in dic1:
    if dic2.get(key):
        ls = []
        ls.append(dic1[key])
        ls.append(dic2[key])
        dic[key] = ls
    else:
        dic[key] = dic1[key]
for key in dic2:
    if dic1.get(key):
        pass
    else:
        dic[key] = dic2[key]

print(dic)
