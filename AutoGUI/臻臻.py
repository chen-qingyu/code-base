import pyautogui
import time

time.sleep(10)

pyautogui.PAUSE = 0.5

pyautogui.click('start.png')
pyautogui.move(100, -100)
pyautogui.click()
pyautogui.click('sublime.png')

pyautogui.press(['z', 'f', 'z', 'f'])
pyautogui.press('1')
pyautogui.press('!')
pyautogui.press(['z', 'f', 'z', 'f'])
pyautogui.press('1')
pyautogui.press('~')
