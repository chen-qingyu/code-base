def check1(s: str) -> int:
    SYMBOLS = {'{': '}', '[': ']', '(': ')', '<': '>'}
    SYMBOLS_L, SYMBOLS_R = SYMBOLS.keys(), SYMBOLS.values()
    stack = []
    depth = 0
    max_depth = 0

    for c in s:
        if c in SYMBOLS_L:  # is an opening grouping symbol
            stack.append(c)
            depth += 1
            max_depth = max(depth, max_depth)
        elif c in SYMBOLS_R:  # is a closing grouping symbol
            if stack != [] and SYMBOLS[stack.pop()] == c:
                depth -= 1
            else:  # nothing to match with or wrong type of closing symbol
                return 0

    return max_depth if stack == [] else 0  # every symbol matched if stack is empty


def check2(s: str) -> int:
    SYMBOLS = {'}': '{', ']': '[', ')': '(', '>': '<'}
    depth = 0
    max_depth = 0

    def preprocess(s):
        return list(filter(lambda c: (c in SYMBOLS.keys()) or (c in SYMBOLS.values()), list(s)))

    def process(stack, loc):
        nonlocal depth
        nonlocal max_depth
        if loc == []:
            return stack
        elif stack != [] and stack[-1] == SYMBOLS.get(loc[0], ''):
            stack.pop()
            depth -= 1
            return process(stack, loc[1:])
        else:
            stack.append(loc[0])
            depth += 1
            max_depth = max(depth, max_depth)
            return process(stack, loc[1:])

    return max_depth if process([], preprocess(s)) == [] else 0


print(check1("<>()"))
print(check1("{[()()]}"))
print(check1("{ [}]"))
print(check1("{ [hello]} "))
print(check1("( [ ( a + b ) * c + d * e ] / { ( f + g ) – h } )"))
print()
print(check2("<>()"))
print(check2("{[()()]}"))
print(check2("{ [}]"))
print(check2("{ [hello]} "))
print(check2("( [ ( a + b ) * c + d * e ] / { ( f + g ) – h } )"))
