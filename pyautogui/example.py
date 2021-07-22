import pyautogui

pyautogui.PAUSE = 1

pyautogui.click('start.png')
pyautogui.click('sublime.png')
pyautogui.write('print("Hello PyAutoGUI!")\n')
