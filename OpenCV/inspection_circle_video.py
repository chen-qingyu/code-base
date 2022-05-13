import cv2


capture = cv2.VideoCapture(0)  # 打开摄像头
while True:
    ret, frame = capture.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 100,
                               param1=100, param2=40, minRadius=10, maxRadius=100)
    if circles is None:
        if cv2.waitKey(20) == ord(' '):
            break
        cv2.imshow('circle detection', frame)
        continue
    print("total: %d" % len(circles[0]))
    for circle in circles[0]:
        x, y = int(circle[0]), int(circle[1])
        r = int(circle[2])
        frame = cv2.circle(frame, (x, y), r, (0, 0, 255), 3)
        frame = cv2.circle(frame, (x, y), 2, (255, 255, 0), -1)
        print("x = %d, y = %d, r = %d" % (x, y, r))
    cv2.imshow('circle detection', frame)

    if cv2.waitKey(20) == ord(' '):  # 刷新周期为20ms，即FPS为50，按空格退出
        break

cv2.destroyAllWindows()
