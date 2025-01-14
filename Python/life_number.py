"""
ref https://www.bilibili.com/video/BV11x411f7vz

1: 领导者。
灵感、鼓舞
最可能成功和出名的
让心愿显化的能力最强
大局导向

2: 共情者。
和谐、直觉
共情者
读心能力
有亲和力

3: 创造者。
创造、孕育
喉轮能量强
创造性表达
会说话操控
容易任性且不专情

4: 实干者。
能力、决心
受尊敬
全身心投入

5: 冒险者。
改变、混沌、冒险
无法驯化
诱人的邪魅
抗压，反对不公正
容易极端导致自毁

6: 博爱者。
共情、创造
心轮能量强
理解和关怀
地球天使
擅长经营健康忠贞的亲密关系

7: 博学者。
知识、智力
敏捷、高智商
过度思虑
攻克难题

8: 富裕者。
富有、丰盛
强者、老练
自然地受人尊敬
有些会选择失败
深受业力影响

9: 治愈者。
有深度的艺术家
能从悲伤和忧郁中创造艺术
深沉的情感和深沉的痛苦
有疗愈的天性
老灵魂了

11: 星际种子。
强大的灵性洞察力
通灵能力
从精神上照亮他人
领导、鼓舞
直觉力

22: 星际种子。
创造一些为世界带来积极改变的东西
和别人不一样

33: 星际种子。
灵性导师
传授知识
"""


def life_number(name: str, birthday: str):
    # 算生命灵数的函数
    # name: string.
    # birthday: 8-digit number string, format: "yyyymmdd".
    path = []
    num = sum(list(map(int, list(birthday))))
    path.append(num)
    while num >= 10 and (num not in [11, 22, 33]):
        num = sum(list(map(int, list(str(num)))))
        path.append(num)
    print(name + "的生命灵数路径是：", path)


life_number("青羽", "19981001")
