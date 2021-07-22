import cv2


frame = cv2.imread('test.jpg')
gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 100,
                           param1=100, param2=40, minRadius=10, maxRadius=100)
for circle in circles[0]:
    x, y = int(circle[0]), int(circle[1])
    r = int(circle[2])
    frame = cv2.circle(frame, (x, y), r, (0, 0, 255), 3)
    frame = cv2.circle(frame, (x, y), 2, (255, 255, 0), -1)
    print("x = %d, y = %d, r = %d" % (x, y, r))
cv2.imwrite('result.jpg', frame)
