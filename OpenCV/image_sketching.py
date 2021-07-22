import cv2

frame = cv2.imread("test.jpg")

grayscale = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)  # 将每一帧转为灰度图
blur = cv2.GaussianBlur(grayscale, (11, 11), 0)  # 将灰度图高斯模糊
binary = cv2.adaptiveThreshold(
    blur, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)  # 将模糊图自适应二值化
final = cv2.morphologyEx(binary, cv2.MORPH_OPEN, cv2.getStructuringElement(
    cv2.MORPH_RECT, (2, 2)))  # 将二值化后的图做开运算

cv2.imwrite("bin.jpg", final)
