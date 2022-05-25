def bit_inverse(num: str) -> str:
    """
    Binary number bit-inversion.
      bit_inverse("0000") -> "1111"
      bit_inverse("1010") -> "0101"

    :param num: a binary number
    :return: binary number after bit-inversion
    """
    return ''.join(map(lambda c: "0" if c == "1" else "1", num))


assert bit_inverse("0000") == "1111"
assert bit_inverse("1010") == "0101"


def bit_plus_one(num: str) -> str:
    """
    Binary number plus one.
      bit_plus_one("0000") -> "0001"
      bit_plus_one("1111") -> "0000"

    :param num: a binary number
    :return: binary number after adding one
    """
    bits = len(num)
    num = bin(eval("0b" + num) + 0b1).removeprefix("0b")
    while len(num) <= bits:  # 补零至原长度
        num = "0" + num
    return num[-bits:]  # 丢弃溢出位


assert bit_plus_one("0000") == "0001"
assert bit_plus_one("1111") == "0000"


def binary_form(num: str, base=10) -> str:
    """
    To convert a number into its binary form.
      binary_form("3") -> "+11"
      binary_form("-3") -> "-11"
      binary_form("11", 2) -> "+11"
      binary_form("-11", 2) -> "-11"

    :param num: a number
    :param base: base system, 2 or 10
    :return: binary form of num
    """
    sign_bit = '+' if num[0] != '-' else '-'
    num = num.lstrip("+-")

    if base == 10:
        num = bin(eval(num)).removeprefix("0b")
    elif base == 2:
        pass
    else:
        raise RuntimeError("The base can only be 2 or 10")

    return sign_bit + num


assert binary_form("3") == "+11"
assert binary_form("-3") == "-11"
assert binary_form("11", 2) == "+11"
assert binary_form("-11", 2) == "-11"


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
    :return: true form of num
    """
    num = binary_form(num, base)

    sign_bit = '0' if num[0] == '+' else '1'
    num = num.lstrip("+-0")

    if len(num) > word_length - 1:
        raise ValueError("Machine word length is not enough")

    # 原码等于二进制符号位 +: 0, -: 1，数值位不变，一共字长位
    while len(num) != word_length - 1:
        num = "0" + num

    return sign_bit + num


assert true_form("0", 4) == "0000"
assert true_form("7", 4) == "0111"
try:
    true_form("8", 4)
except ValueError as e:
    assert e.args[0] == "Machine word length is not enough"
assert true_form("8") == "00001000"
assert true_form("-0", 4) == "1000"
assert true_form("-7", 4) == "1111"
assert true_form("101", 4, 2) == "0101"
assert true_form("00000101", 4, 2) == "0101"
assert true_form("-0101", 4, 2) == "1101"


def inverse_form(num: str, word_length=8, base=10) -> str:
    num = true_form(num, word_length, base)

    if num[0] == "0":  # 正数反码等于原码
        inverse = num
    else:  # 负数反码等于原码符号位不变，数值位取反
        inverse = num[0] + bit_inverse(num[1:])

    return inverse


assert inverse_form("0") == "00000000"
assert inverse_form("-0") == "11111111"
assert inverse_form("1") == "00000001"
assert inverse_form("-1") == "11111110"


def complement_form(num: str, word_length=8, base=10) -> str:
    num = inverse_form(num, word_length, base)

    if num[0] == "0":  # 正数补码等于反码
        complement = num
    else:  # 负数补码等于反码加一
        complement = bit_plus_one(num)

    return complement


assert complement_form("0") == "00000000"
assert complement_form("-0") == "00000000"
assert complement_form("-1") == "11111111"
assert complement_form("+5") == "00000101"


def shift_form(num: str, word_length=8, base=10) -> str:
    num = complement_form(num, word_length, base)

    # 移码等于补码符号位取反
    shift = ("0" if num[0] == "1" else "1") + num[1:]

    return shift


assert shift_form("0") == "10000000"
assert shift_form("-0") == "10000000"
assert shift_form("-1") == "01111111"
assert shift_form("+5") == "10000101"


def machine_representation(num: str, word_length=8, base=10) -> dict:
    d = {
        "真值": num,
        "二进制": binary_form(num, base),
        "原码": true_form(num, word_length, base),
        "反码": inverse_form(num, word_length, base),
        "补码": complement_form(num, word_length, base),
        "移码": shift_form(num, word_length, base)
    }

    return d


# for number in ["-5", "-2", "-1", "-0", "0", "1", "2", "5"]:
#     for desc, code in machine_representation(number).items():
#         print(desc + ": " + code[:4] + " " + code[4:])
#     print()

def bit_add(x: str, y: str) -> str:
    if len(x) != len(y):
        raise RuntimeError("x's and y's bits are required to be equal")

    word_length = len(x)
    num = bin(eval("0b" + x) + eval("0b" + y)).removeprefix("0b")[-word_length:]
    while len(num) != word_length:
        num = "0" + num
    return num


def booth(x: str, y: str, word_length=5, base=2, print_step=False) -> str:
    """
    Booth algorithm.
      booth("-0.1101", "0.1011") -> "-0.10001111"

    :param x: a number
    :param y: a number
    :param word_length: machine word length
    :param base: base system, 2 or 10
    :param print_step: whether print steps
    :return: binary representation of the result of multiplication
    """
    is_decimal = False
    if '.' in x and '.' in y:
        is_decimal = True
        x = x.replace('.', '')
        y = y.replace('.', '')

    x = complement_form(x, word_length, base)
    x = x[0] + x

    mx = bit_plus_one(bit_inverse(x))

    y = complement_form(y, word_length, base)
    y = y + "0"

    if print_step:
        print(f"[x]双符号补={x}, [-x]双符号补={mx}, [y]补添零={y}")

    # 高位部分积
    hp = "0" * (word_length + 1)

    # 低位部分积
    lp = ""

    for i in range(word_length):
        if print_step:
            print(f"step {i + 1}: hp='{hp}', lp='{lp}', y[-2:]='{y[-2:]}', "
                  + ("adding & shifting..." if i != word_length - 1 else "adding..."))

        if y[-2:] == "00" or y[-2:] == "11":
            pass
        elif y[-2:] == "01":
            hp = bit_add(hp, x)
        elif y[-2:] == "10":
            hp = bit_add(hp, mx)

        if i == word_length - 1:
            if print_step:
                print(f"final : hp='{hp}', lp='{lp}'")
            break

        # 部分积右移一位
        lp = hp[-1] + lp
        hp = (hp[0] + hp)[:word_length + 1]
        # y右移一位
        y = y[:-1]

    # 乘积的补码
    complement = hp[1:] + lp
    is_positive_or_0 = True if hp[0] == '0' else False

    # 从补码到原码
    if is_positive_or_0:
        origin = complement
    else:
        origin = complement[0] + bit_plus_one(bit_inverse(complement[1:]))

    # 处理小数，取绝对值
    if is_decimal:
        num = "0." + origin[1:]
    else:
        num = origin[1:]

    # 添加符号
    return ('+' if is_positive_or_0 else '-') + num


assert booth("-0.1101", "0.1011", print_step=False) == "-0.10001111"
assert booth("2", "4", base=10, print_step=False) == "+00001000"
assert booth("-2", "4", base=10, print_step=False) == "-00001000"
assert booth("2", "-4", base=10, print_step=False) == "-00001000"
assert booth("-2", "-4", base=10, print_step=False) == "+00001000"
assert booth("1", "1", base=10, print_step=False) == "+00000001"
