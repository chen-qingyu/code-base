import functools


def hamming_encode(bits: list[int]) -> list[int]:
    """
    Encoding a string of bits to extended Hamming code.

    >>> hamming_encode([0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0])
    [0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0]
    >>> hamming_encode([0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1])
    [1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1]
    """

    # copy list
    code = list(bits)

    # global parity bit
    code.insert(0, 0)

    # Hamming code check bits
    index = 1
    while index < len(code):
        code.insert(index, 0)
        index <<= 1

    # calculate Hamming code check bits
    index = 1
    while index < len(code):
        code[index] = functools.reduce(lambda x, y: x ^ y, [bit for (i, bit) in enumerate(code) if bit and (i & index)])
        index <<= 1

    # calculate global parity bit
    code[0] = functools.reduce(lambda x, y: x ^ y, [bit for bit in code if bit])

    return code


def hamming_decode(bits: list[int]):
    """
    Decoding a string of bits of extended Hamming code.

    >>> hamming_decode([0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0])
    'OK'
    >>> hamming_decode([0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1])
    'Bit 15 error'
    >>> hamming_decode([1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1])
    'OK'
    >>> hamming_decode([0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1])
    'Error with at least two bits'
    """

    # the index of the error bit
    index = functools.reduce(lambda x, y: x ^ y, [i for (i, bit) in enumerate(bits) if bit])

    # global parity bit
    parity = functools.reduce(lambda x, y: x ^ y, [bit for bit in bits if bit])

    if index == 0 and parity == 0:
        return "OK"
    elif index == 0 and parity == 1:
        return "Error with at least two bits"
    else:
        return f"Bit {index} error"


if __name__ == "__main__":
    import doctest
    doctest.testmod()
