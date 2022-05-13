import cv2

cap = cv2.VideoCapture("test.mp4")  # 实例化一个视频对象

while True:
    ret, frame = cap.read()  # 读取视频的每一帧
    if frame is None:  # 最后一帧读取完就退出
        break

    grayscale = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)  # 将每一帧转为灰度图
    blur = cv2.GaussianBlur(grayscale, (5, 5), 0)  # 将灰度图高斯模糊
    binary = cv2.adaptiveThreshold(
        blur, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 5, 2)  # 将模糊图自适应二值化
    final = cv2.bitwise_not(cv2.morphologyEx(cv2.bitwise_not(
        binary), cv2.MORPH_OPEN, cv2.getStructuringElement(cv2.MORPH_RECT, (2, 2))))  # 将二值化后的图做开运算

    cv2.imshow('final', final)

    if cv2.waitKey(20) & 0xFF == ord(' '):  # 刷新周期为20ms，即FPS为50，可以按空格退出
        break
