import pyautogui
import time

print("Press Ctrl-C to quit.")

try:
    while True:
        x, y = pyautogui.position()
        print("X: {:4d} Y: {:4d}".format(x, y), end='\r')
        # 实测加上这一行几乎不影响使用但CPU占用率从30%左右降到了10%左右
        time.sleep(0.01)
except KeyboardInterrupt:
    print('\n')
