import os
import cv2

path = './images/'
suffix = '.png'

fps = 24  # 视频每秒24帧
size = (640, 480)  # 需要转为视频的图片的尺寸

video = cv2.VideoWriter("video.avi", cv2.VideoWriter_fourcc('I', '4', '2', '0'), fps, size)

for item in os.listdir(path):
    if item.endswith(suffix):
        img = cv2.imread(path + item)
        video.write(img)

video.release()
cv2.destroyAllWindows()
