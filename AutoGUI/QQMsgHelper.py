import pyautogui
import time

'''
QQ消息群发脚本

打开待群发的分组，运行脚本PAUSE秒内选中QQ主界面，之后自动将剪贴板内容群发
'''

PAUSE = 3
N = 10

# 暂停PAUSE秒以选中QQ主界面
time.sleep(PAUSE)

# 循环发送剪贴板消息N次
for i in range(N):
    pyautogui.press('tab', presses=5)  # 实测，选中分组界面
    pyautogui.press('down')  # 往下一个
    pyautogui.press('enter')  # 打开对话框
    pyautogui.hotkey('ctrl', 'v')  # 粘贴剪贴板内容到对话框
    # pyautogui.press('enter')  # 发送
    pyautogui.press('esc')  # 关闭对话框
