import requests

hd = {'user-agent': 'Mozilla/5.0'}
url = "http://www.opencv.org.cn/opencvdoc/2.3.2/html/_images/general.jpg"
path = "./img.jpg"

if __name__ == '__main__':
    try:
        r = requests.get(url, headers=hd)
        r.raise_for_status()
        with open(path, 'wb') as f:
            f.write(r.content)
        print("OK")
    except Exception as e:
        print(e)
