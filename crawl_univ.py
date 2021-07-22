import requests
import bs4


def getHTMLText(url):
    hd = {'user-agent': 'Mozilla/5.0'}
    try:
        r = requests.get(url, headers=hd)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except Exception:
        return ""


def fillUnivList(ls, text):
    soup = bs4.BeautifulSoup(text, 'html.parser')
    for tr in soup.find('tbody').children:
        if isinstance(tr, bs4.element.Tag):
            tds = tr('td')
            ls.append([tds[0].string, tds[1].string, tds[3].string])


def printUnivList(ls, num):
    print("{0:^10}\t{1:{3}^10}\t{2:^10}".format("排名", "学校", "总分", chr(12288)))
    for i in range(num):
        u = ls[i]
        print("{0:^10}\t{1:{3}^10}\t{2:^10}".format(u[0], u[1], u[2], chr(12288)))


def main():
    univNum = 20
    info = []
    url = "http://www.zuihaodaxue.com/zuihaodaxuepaiming2019.html"
    text = getHTMLText(url)
    fillUnivList(info, text)
    printUnivList(info, univNum)
    input()


if __name__ == "__main__":
    main()
