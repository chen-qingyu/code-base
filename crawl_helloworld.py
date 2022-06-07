import requests
import bs4
import os


def get_html_text(url):
    hd = {'user-agent': 'Mozilla/5.0'}
    r = requests.get(url, headers=hd)
    r.raise_for_status()
    r.encoding = r.apparent_encoding
    return r.text


def find_next_tag(current: bs4.element.Tag, tag="", stop="") -> bs4.element.Tag | None:
    """
    Find the next specified tag.

    :param current: start with the current tag
    :param tag: Specifies the name of the next tag, and the default empty string represents any tag
    :param stop: stop searching when this tag is encountered, and the default empty string represents don't stop
    :return: the next specified tag, or None if not found
    """

    if tag:
        while not (isinstance(current.next_sibling, bs4.element.Tag) and current.next_sibling.name == tag):
            current = current.next_sibling
            if stop and isinstance(current.next_sibling, bs4.element.Tag) and current.next_sibling.name == stop:
                return None
    else:
        while not isinstance(current.next_sibling, bs4.element.Tag):
            current = current.next_sibling
    return current.next_sibling


def write_helloworld(text: str, dir_name="./helloworld/"):
    """
    Parse HTML text and write to code file.

    A typical fragment is:
        <table width="100%"><tr>
        <td><h2>1C-Enterprise</h2></td>
        <td align="right"><small><a href="#index">返回到索引</a></small></td>
        </tr></table>
        <pre>
        // Hello World in 1C:Enterprise built-in script language

        Message("Hello, World!");
        </pre>

    :param text: HTML text
    :param dir_name: code file storage directory
    """

    if not os.path.exists(dir_name):
        os.mkdir(dir_name)

    soup = bs4.BeautifulSoup(text, 'html.parser')

    for table in soup.find_all("table", attrs={"width": "100%"}):
        with open(dir_name + str(table.tr.td.string) + ".helloworld", "w", encoding='utf-8') as fo:
            try:
                fo.write(find_next_tag(table, "pre", "img").text.strip() + '\n')
            except AttributeError:
                fo.write("Something wrong")


def main():
    html_text = get_html_text("https://netsmell.com/apps/helloworldcollection/hello.htm")
    write_helloworld(html_text)


if __name__ == "__main__":
    main()
