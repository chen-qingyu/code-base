import os

BeginOfSlices = 1
EndOfSlices = 999
VideoName = "new.ts"

result = "copy /b "
for x in range(BeginOfSlices, EndOfSlices):
    result += str(x) + "+"
result += str(EndOfSlices)
result += " " + VideoName

os.system(result)
