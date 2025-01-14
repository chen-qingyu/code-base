import functools


def soundex_encoding(string: str) -> str:
    """
    >>> soundex_encoding('Aerc')
    'A620'
    >>> soundex_encoding('Earc')
    'E620'
    >>> soundex_encoding('Taylor')
    'T460'
    >>> soundex_encoding('Ttttaylor')
    'T460'
    >>> soundex_encoding('ChenQingyu~')
    'C525'
    """

    SOUNDEX_MAP = {
        'A': '0', 'B': '1', 'C': '2', 'D': '3', 'E': '0',
        'F': '1', 'G': '2', 'H': '0', 'I': '0', 'J': '2',
        'K': '2', 'L': '4', 'M': '5', 'N': '5', 'O': '0',
        'P': '1', 'Q': '2', 'R': '6', 'S': '2', 'T': '3',
        'U': '0', 'V': '1', 'W': '0', 'X': '2', 'Y': '0',
        'Z': '2'}

    string = string.upper()

    mapped = map(lambda c: SOUNDEX_MAP.get(c, '0'), string[1:])
    filtered = filter(lambda c: c != '0', mapped)
    code = functools.reduce(lambda s, c: s + (c if c != s[-1] else ""), filtered)

    code = code[1:] if SOUNDEX_MAP[string[0]] == code[0] else code
    code = code.ljust(3, '0')

    return string[0] + code[:3]


if __name__ == "__main__":
    import doctest
    doctest.testmod()
