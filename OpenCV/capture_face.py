import cv2
import os
import time

# 照片储存目录
dir_name = "photos"
if not os.path.exists(dir_name):
    os.mkdir(dir_name)

# 照片储存尺寸
(WIDTH, HEIGHT) = (640, 480)

# 用户操作提示
print(f"Photo taking applet, photos stored in the \"{dir_name}\" directory by size {(WIDTH, HEIGHT)}")
print("C: Capture")
print("Q: Quit")

# 实例化一个相机
camera = cv2.VideoCapture(0)
camera.set(cv2.CAP_PROP_FRAME_WIDTH, WIDTH)
camera.set(cv2.CAP_PROP_FRAME_HEIGHT, HEIGHT)

while True:
    _, frame = camera.read()

    # 镜像显示
    frame = cv2.flip(frame, 1, dst=None)
    cv2.imshow("capture", frame)

    key = cv2.waitKey(1)

    # 拍照
    if key == ord('c') or key == ord('C'):
        img_path = "%s/%d.jpg" % (dir_name, time.time_ns())
        cv2.imwrite(img_path, frame)
        print("%s saved." % img_path)

    # 退出
    if key == ord('q') or key == ord('Q'):
        break

# 关闭窗口
camera.release()
cv2.destroyAllWindows()
