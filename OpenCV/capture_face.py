import cv2
import os

# 用户操作提示
print("===========================================")
print("=  热键（请在摄像头的窗口使用）             =")
print("=  x: 拍照                                =")
print("=  q: 退出                                =")
print("===========================================")

# 创建存储目录
dir_name = input("请输入存储目录：")
while os.path.exists(dir_name):
    dir_name = input("目录已存在！请重新输入存储目录：")
os.mkdir(dir_name)

# 初始化各种参数
index = 1
cap = cv2.VideoCapture(0)  # 实例化一个相机
width = 640
height = 480
w = 360
cap.set(cv2.CAP_PROP_FRAME_WIDTH, width)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, height)
crop_w_start = (width-w)//2
crop_h_start = (height-w)//2

# 储存的照片大小
(WIDTH, HEIGHT) = (224, 224)

while True:
    ret, frame = cap.read()

    # 重新调整每一帧大小
    frame = frame[crop_h_start:crop_h_start+w, crop_w_start:crop_w_start+w]

    # 镜像显示
    frame = cv2.flip(frame, 1, dst=None)
    cv2.imshow("capture", frame)

    input = cv2.waitKey(1) & 0xFF

    # 拍照
    if input == ord('x'):
        cv2.imwrite("%s/%d.jpg" % (dir_name, index), cv2.resize(frame, (WIDTH, HEIGHT), interpolation=cv2.INTER_AREA))
        print("%s/%d.jpg" % (dir_name, index))
        index += 1

    # 退出
    if input == ord('q'):
        break

# 关闭窗口
cap.release()
cv2.destroyAllWindows()
