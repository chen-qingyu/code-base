import os

# resolution, in DPI (default is 150)
resolution = 600
# enable font anti-aliasing: yes, no
aa = "yes"
# enable vector anti-aliasing: yes, no
aaVector = "yes"

files = os.listdir(".")
for fname in files:
    if fname[-4:] == ".pdf":
        os.system(f"pdftoppm -r {resolution} -aa {aa} -aaVector {aaVector} -png \"./{fname}\" \"{fname[:-4]}\"")

print("OK.")
