import wordcloud  # 绘制词云
import jieba  # 中文分词
import matplotlib.image  # 读取图片

# 读取文本内容
with open("./data/yuri.txt", encoding="utf-8") as fo:
    txt = fo.read()

# 分词
words = jieba.cut(txt)

# 加载停用词
with open("./data/hit_stopwords.txt", encoding="utf-8") as fo:
    stopwords = fo.read().split()

# 过滤停用词
words = filter(lambda word: word not in stopwords, words)

# 配置词云图参数
mask = matplotlib.image.imread("./images/mask.jpg")  # 形状，可选
font = "./fonts/方正楷体简体.TTF"  # 字体，显示中文必备

# 生成词云对象
w = wordcloud.WordCloud(mask=mask, font_path=font, background_color="white")

# 生成词云图
w.generate(" ".join(words))
w.to_file("./result.png")
