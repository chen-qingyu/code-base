import jieba

file_name = input("请输入要分析的文件名： ")
with open(file_name, encoding="utf-8") as fo:
    words = jieba.lcut(fo.read())

counts = {}
for word in words:
    if len(word) != 1:
        counts[word] = counts.get(word, 0) + 1

items = list(counts.items())
items.sort(key=lambda x: x[1], reverse=True)

for i in range(15):
    word, count = items[i]
    print("{:10}{:}".format(word, count))
