import os

max_slices = 999
video_name = "new.ts"

result = "copy /b "
for x in range(1, max_slices):
    result += str(x) + "+"
result += str(max_slices)
result += " " + video_name

os.system(result)
