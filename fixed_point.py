def bit_inverse(num: str) -> str:
    """
    Binary number bit-inversion.
      bit_inverse("0000") -> "1111"
      bit_inverse("1010") -> "0101"

    :param num: a binary number
    :return: binary number after bit-inversion
    """
    return ''.join(map(lambda c: "0" if c == "1" else "1", num))


def plus_one(num: str) -> str:
    """
    Binary number plus one.
      plus_one("0000") -> "0001"
      plus_one("1111") -> "0000"

    :param num: a binary number
    :return: binary number after adding one
    """
    bits = len(num)
    num = bin(eval("0b" + num) + 0b1).removeprefix("0b")
    while len(num) <= bits:  # 补零至原长度
        num = "0" + num
    return num[-bits:]  # 丢弃溢出位


def true_form(num: str, word_length=8, base=10) -> str:
    """
    To convert a number into its true form.
      true_form("0", 4) -> "0000"
      true_form("7", 4) -> "0111"
      true_form("8", 4) -> ValueError: Machine word length is not enough
      true_form("8") -> "00001000"
      true_form("-0", 4) -> "1000"
      true_form("-7", 4) -> "1111"
      true_form("101", 4, 2) -> "0101"
      true_form("00000101", 4, 2) -> "0101"
      true_form("-0101", 4, 2) -> "1101"

    :param num: a number
    :param word_length: machine word length
    :param base: base system, 2 or 10
    :return: num's true form
    """
    sign_bit = '0' if num[0] != '-' else '1'

    num = num.lstrip("+-0")

    if base == 10:
        num = bin(eval(num)).removeprefix("0b")
    elif base == 2:
        pass
    else:
        raise RuntimeError("The base can only be 2 or 10")

    if len(num) > word_length - 1:
        raise ValueError("Machine word length is not enough")

    while len(num) != word_length - 1:
        num = "0" + num

    return sign_bit + num


def complement_form(num: str) -> str:
    """
    Change the true form of a number into the complement form.

    :param num: a binary number in its true form
    :return: a binary number in its complement form
    """

    if num[0] == "0":  # 正数
        inverse = num  # 反码等于原码
        complement = inverse  # 补码等于反码
    else:  # 负数
        inverse = "1" + bit_inverse(num[1:])  # 反码等于原码符号位不变，数值位按位取反
        complement = plus_one(inverse)  # 补码等于反码加一

    return complement


def machine_representation(x: str, word_length: int = 8) -> dict:
    d = {"真值": x}

    # 二进制
    x_bin = bin(eval(x)).replace("0b", "")
    x_bin = ('+' + x_bin if x[0] != '-' else x_bin)
    d["二进制"] = x_bin

    # 原码
    # 原码等于二进制符号位 +: 0, -: 1，数值位不变，一共字长位
    true_form = x_bin[0] + ("0" * (word_length - 1 - len(x_bin[1:]))) + x_bin[1:]
    true_form = ("0" if true_form[0] == "+" else "1") + true_form[1:]
    d["原码"] = true_form

    # 反码
    if true_form[0] == "0":  # 正数反码等于原码
        inverse = true_form
    else:  # 负数反码等于原码符号位不变，数值位取反
        inverse = "1" + ''.join(map(lambda c: "0" if c == "1" else "1", true_form[1:]))
    d["反码"] = inverse

    # 补码
    if inverse[0] == "0":  # 正数补码等于反码
        complement = inverse
    else:  # 负数补码等于反码加一
        complement = bin(eval("0b" + inverse) + 1)[-8:]
    d["补码"] = complement

    # 移码
    # 移码等于补码符号位取反
    shift = ("0" if complement[0] == "1" else "1") + complement[1:]
    d["移码"] = shift

    return d


# for X in ["-5", "-2", "-1", "-0", "0", "1", "2", "5"]:
#     for desc, code in machine_representation(X).items():
#         print(desc + ": " + code[:4] + " " + code[4:])
#     print()


def booth(x: str, y: str) -> str:
    # 机器字长
    word_len = 5
    # 数值位长
    n = word_len - 1

    # x = x.replace('.', '')
    # y = y.replace('.', '')

    if x[0] != '-':  # 正数
        mx = "11" + bin(eval("0b" + (''.join(map(lambda c: "0" if c == "1" else "1", (x.split(".")[1]))))) + 1).replace(
            "0b", "")
        x = "00" + x.split(".")[1]
    else:
        mx = "00" + x.split(".")[1]
        x = bin(eval("0b" + ''.join(map(lambda c: "0" if c == "1" else "1", (x.split(".")[1])))) + 1).replace("0b", "")
        while len(x) != n:
            x = "0" + x
        x = "11" + x

    if y[0] != '-':
        y = "0" + y.split(".")[1] + "0"
    else:
        y = "1" + bin(eval("0b" + (''.join(map(lambda c: "0" if c == "1" else "1", (y.split(".")[1]))))) + 1)[-n:] + "0"

    # 高位部分积
    hp = "0" * (n + 2)

    # 低位部分积
    lp = ""

    for i in range(word_len):
        if y[-2:] == "00" or y[-2:] == "11":
            pass
        elif y[-2:] == "01":
            hp = bin(eval("0b" + hp) + eval("0b" + x))[2:][-(n + 2):]
        elif y[-2:] == "10":
            hp = bin(eval("0b" + hp) + eval("0b" + mx))[2:][-(n + 2):]

        while len(hp) != n + 2:
            hp = "0" + hp

        print(hp, "---", lp)

        if i == word_len - 1:
            break

        lp = hp[-1] + lp
        hp = (hp[0] + hp)[:n + 2]
        y = y[:-1]

    return hp + lp

# print(booth("-0.1101", "0.1011"))
