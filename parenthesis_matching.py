def check1(s):
    SYMBOLS = {'}': '{', ']': '[', ')': '(', '>': '<'}
    SYMBOLS_L, SYMBOLS_R = SYMBOLS.values(), SYMBOLS.keys()
    stack = []
    depth = 0
    max_depth = 0

    for c in s:
        if c in SYMBOLS_L:
            stack.append(c)
            depth += 1
            max_depth = max(depth, max_depth)
        elif c in SYMBOLS_R:
            if stack != [] and stack[-1] == SYMBOLS[c]:
                stack.pop()
                depth -= 1
            else:
                return 0

    return max_depth if stack == [] else 0


def check2(s):
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
print()
print(check2("<>()"))
print(check2("{[()()]}"))
print(check2("{ [}]"))
print(check2("{ [hello]} "))
