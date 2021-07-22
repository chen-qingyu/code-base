import requests

hd = {'user-agent': 'Mozilla/5.0'}
url = "https://isujin.com/wp-content/uploads/2017/12/wallhaven-594603.jpg"
path = "./img.jpg"

try:
    r = requests.get(url, headers=hd)
    r.raise_for_status()
except Exception:
    input("Error!")
    exit(1)

with open(path, 'wb') as f:
    f.write(r.content)
