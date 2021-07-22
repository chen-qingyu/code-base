import os
import time
print('\n'.join([' '.join([('Love'[(x - y) % len('Love')] if((x * 0.05)**2 + (y * 0.1)**2 - 1)**3 -
                            (x * 0.05)**2 * (y * 0.1)**3 <= 0 else ' ') for x in range(-30, 30)]) for y in range(30, -30, -1)]))
print("请向上滑动↑")
colors = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"]
while True:
    for color in colors:
        os.system("color d" + color)
        time.sleep(0.5)
