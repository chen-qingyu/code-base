def hanoi(layer: int):
    ls = []

    def _hanoi(layer, src, mid, dst):
        nonlocal ls
        if layer == 1:
            ls.append("layer {}: {}->{}".format(1, src, dst))
        else:
            _hanoi(layer - 1, src, dst, mid)
            ls.append("layer {}: {}->{}".format(layer, src, dst))
            _hanoi(layer - 1, mid, src, dst)

    _hanoi(layer, "A", "B", "C")
    return ls


n = eval(input("Please enter an integer representing the number of layers in Tower of Hanoi: "))
steps = hanoi(n)
print("process:", steps)
print("total steps:", len(steps))
