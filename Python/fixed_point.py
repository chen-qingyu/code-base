def bit_inverse(num: str) -> str:
    """
    Binary integer bit-inversion.

    :param num: a binary integer
    :return: binary integer after bit-inversion

    >>> bit_inverse("0000")
    '1111'
    >>> bit_inverse("1010")
    '0101'
    """
    return ''.join(map(lambda c: "0" if c == "1" else "1", num))


def bit_plus_one(num: str) -> str:
    """
    Binary integer plus one.

    :param num: a binary integer
    :return: binary integer after adding one

    >>> bit_plus_one("0000")
    '0001'
    >>> bit_plus_one("1111")
    '0000'
    """
    bits = len(num)
    num = bin(int(num, 2) + 1)[2:].rjust(bits, '0')
    return num[-bits:]  # 丢弃溢出位


def binary_form(num: str, base=10) -> str:
    """
    Convert an integer into its binary form.

    :param num: an integer
    :param base: base system, 2 or 10
    :return: binary form of num

    >>> binary_form("3")
    '+11'
    >>> binary_form("-3")
    '-11'
    >>> binary_form("11", 2)
    '+11'
    >>> binary_form("-11", 2)
    '-11'
    """
    if base not in (2, 10):
        raise RuntimeError("The base can only be 2 or 10")

    sign_bit = '+' if num[0] != '-' else '-'
    num = bin(int(num.lstrip("+-"), base))[2:]

    return sign_bit + num


def true_form(num: str, word_length=8, base=10) -> str:
    """
    Convert an integer into its true form.

    :param num: an integer
    :param word_length: machine word length
    :param base: base system, 2 or 10
    :return: true form of num

    >>> true_form("0", 4)
    '0000'
    >>> true_form("7", 4)
    '0111'
    >>> true_form("8", 4)
    Traceback (most recent call last):
        ...
    ValueError: Machine word length is not enough
    >>> true_form("8")
    '00001000'
    >>> true_form("-0", 4)
    '1000'
    >>> true_form("-7", 4)
    '1111'
    >>> true_form("101", 4, 2)
    '0101'
    >>> true_form("00000101", 4, 2)
    '0101'
    >>> true_form("-0101", 4, 2)
    '1101'
    """
    num = binary_form(num, base)

    sign_bit = '0' if num[0] == '+' else '1'
    num = num.lstrip("+-0")

    if len(num) > word_length - 1:
        raise ValueError("Machine word length is not enough")

    # 原码等于二进制符号位 +: 0, -: 1，数值位不变，一共字长位
    return sign_bit + num.rjust(word_length - 1, '0')


def inverse_form(num: str, word_length=8, base=10) -> str:
    """
    Convert an integer into its inverse form.

    >>> inverse_form("0")
    '00000000'
    >>> inverse_form("-0")
    '11111111'
    >>> inverse_form("1")
    '00000001'
    >>> inverse_form("-1")
    '11111110'
    """
    num = true_form(num, word_length, base)

    # 正数反码等于原码；负数反码等于原码符号位不变，数值位取反
    return num if num[0] == "0" else num[0] + bit_inverse(num[1:])


def complement_form(num: str, word_length=8, base=10) -> str:
    """
    Convert an integer into its complement form.

    >>> complement_form("0")
    '00000000'
    >>> complement_form("-0")
    '00000000'
    >>> complement_form("-1")
    '11111111'
    >>> complement_form("+5")
    '00000101'
    """
    num = inverse_form(num, word_length, base)

    # 正数补码等于反码；负数补码等于反码加一
    return num if num[0] == "0" else bit_plus_one(num)


def shift_form(num: str, word_length=8, base=10) -> str:
    """
    Convert an integer into its shift form.

    >>> shift_form("0")
    '10000000'
    >>> shift_form("-0")
    '10000000'
    >>> shift_form("-1")
    '01111111'
    >>> shift_form("+5")
    '10000101'
    """
    num = complement_form(num, word_length, base)

    # 移码等于补码符号位取反
    return bit_inverse(num[0]) + num[1:]


def machine_representation(num: str, word_length=8, base=10) -> dict:
    return {
        "真值": num,
        "二进制": binary_form(num, base),
        "原码": true_form(num, word_length, base),
        "反码": inverse_form(num, word_length, base),
        "补码": complement_form(num, word_length, base),
        "移码": shift_form(num, word_length, base)
    }


# for number in ["-5", "-2", "-1", "-0", "0", "1", "2", "5"]:
#     for desc, code in machine_representation(number).items():
#         print(desc + ": " + code[:4] + " " + code[4:])
#     print()


def bit_add(x: str, y: str) -> str:
    """
    Bit addition.

    >>> bit_add("0", "0")
    '0'
    >>> bit_add("1", "1")
    '0'
    >>> bit_add("01", "10")
    '11'
    >>> bit_add("11", "11")
    '10'
    >>> bit_add("0001", "1110")
    '1111'
    """
    if len(x) != len(y):
        raise RuntimeError("x's and y's bits are required to be equal")

    word_length = len(x)
    return bin(int(x, 2) + int(y, 2))[2:].rjust(word_length, '0')[-word_length:]


def booth(x: str, y: str, word_length=5, base=2, print_step=False) -> str:
    """
    Booth algorithm.

    :param x: a number
    :param y: a number
    :param word_length: machine word length
    :param base: base system, 2 or 10
    :param print_step: whether print steps
    :return: binary representation of the result of multiplication

    >>> booth("-0.1101", "0.1011") 
    '-0.10001111'
    >>> booth("2", "4", base=10) 
    '+00001000'
    >>> booth("-2", "4", base=10)
    '-00001000'
    >>> booth("2", "-4", base=10) 
    '-00001000'
    >>> booth("-2", "-4", base=10)
    '+00001000'
    >>> booth("1", "1", base=10) 
    '+00000001'
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


if __name__ == "__main__":
    import doctest
    doctest.testmod()
