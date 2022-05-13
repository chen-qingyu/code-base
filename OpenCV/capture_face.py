import cv2
import os
import time

# 用户操作提示
print("===========================================")
print("=  X：拍照                                 =")
print("=  Q：退出                                 =")
print("===========================================")

# 照片存储目录
dir_name = "photos"
if not os.path.exists(dir_name):
    os.mkdir(dir_name)

# 初始化各种参数
cap = cv2.VideoCapture(0)  # 实例化一个相机
width = 640
height = 480
w = 360
cap.set(cv2.CAP_PROP_FRAME_WIDTH, width)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, height)
crop_w_start = (width - w) // 2
crop_h_start = (height - w) // 2

# 储存的照片大小
(WIDTH, HEIGHT) = (224, 224)

while True:
    ret, frame = cap.read()

    # 重新调整每一帧大小
    frame = frame[crop_h_start:crop_h_start + w, crop_w_start:crop_w_start + w]

    # 镜像显示
    frame = cv2.flip(frame, 1, dst=None)
    cv2.imshow("capture", frame)

    key = cv2.waitKey(1) & 0xFF

    # 拍照
    if key == ord('x') or key == ord('X'):
        cv2.imwrite("%s/%d.jpg" % (dir_name, int(time.time() * 10)),
                    cv2.resize(frame, (WIDTH, HEIGHT), interpolation=cv2.INTER_AREA))
        print("%s/%d.jpg saved." % (dir_name, int(time.time() * 10)))

    # 退出
    if key == ord('q') or key == ord('Q'):
        break

# 关闭窗口
cap.release()
cv2.destroyAllWindows()
