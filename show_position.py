import pyautogui
import time

print("Press Ctrl-C to quit.")
while True:
    try:
        x, y = pyautogui.position()
        print(f"X: {x:4d} Y: {y:4d}", end='\r')
        time.sleep(0.01)  # 实测加上这一行几乎不影响使用但CPU占用率从30%左右降到了10%左右
    except KeyboardInterrupt:
        break
