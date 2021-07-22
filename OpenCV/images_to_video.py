import os
import cv2

path = './images/'
filelist = os.listdir(path)

fps = 24  # 视频每秒24帧
size = (640, 480)  # 需要转为视频的图片的尺寸

video = cv2.VideoWriter("VideoTest1.avi", cv2.VideoWriter_fourcc('I', '4', '2', '0'), fps, size)

for item in filelist:
    if item.endswith('.png'):
        item = path + item
        img = cv2.imread(item)
        video.write(img)

video.release()
cv2.destroyAllWindows()
