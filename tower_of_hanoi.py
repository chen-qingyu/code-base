def hanoi(layer: int):
    steps = 0

    def _hanoi(layer, src, mid, dst):
        nonlocal steps
        steps += 1
        if layer == 1:
            print("layer {}: {}->{}".format(1, src, dst))
        else:
            _hanoi(layer - 1, src, dst, mid)
            print("layer {}: {}->{}".format(layer, src, dst))
            _hanoi(layer - 1, mid, src, dst)

    _hanoi(layer, "A", "B", "C")
    print(f"Total steps: {steps}")


n = int(input("Please enter an integer representing the number of layers in Tower of Hanoi: "))
hanoi(n)
