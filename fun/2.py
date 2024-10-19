import requests
from bs4 import BeautifulSoup


def getData(url):
    #try:
        head = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) \
             AppleWebKit/537.36 (KHTML, like Gecko) \
             Chrome/116.0.0.0 \
             Safari/537.36 \
             Edg/116.0.1938.62'}
            
        r = requests.get(url, timeout=30, headers=head,proxies={'http':'127.0.0.1:7890'})
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        r.close()
        return r.text
    #except Exception:
    #    print("出现unknown错误")
    #    return ''


def findEveryJpgUrl(webData, mangaList):
    soup = BeautifulSoup(webData, 'html.parser')
    gdtms = soup.find_all('div', class_='gdtm')
    for gdtm in gdtms:
        a = gdtm.find('a')
        mangaList.append(a['href'])
    # print(mangaList)


def findMangaPage(webData, mangaList):
    soup = BeautifulSoup(webData, 'html.parser')
    div = soup.find('div', id='i3')
    img = div.find('img', id='img')
    mangaList.append(img['src'])


def downloadManga(PageList):
    global count
    for page in PageList:
        print("正在保存第{}张".format(count))
        try:
            head = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) \
            AppleWebKit/537.36 (KHTML, like Gecko) \
            Chrome/116.0.0.0 \
            Safari/537.36 \
            Edg/116.0.1938.62'}
            print(page)
            mangaData = requests.get(page, timeout=30, headers=head,proxies={'http':'127.0.0.1:7890'})
            mangaData.raise_for_status()

            with open(str(count) + '.jpg', 'wb+') as manga:
                manga.write(mangaData.content)
            print("第{}张保存成功".format(count))
            count += 1
            mangaData.close()
        except Exception:
            print("第{}张保存失败".format(count))
            continue


count = 1
pages=1   #页数
for j in range(pages):
    mangaUrlList = []
    mangaPageList = []
    print("正在下载第{}页".format(j + 1))
    url = 'https://e-hentai.org/g/3033815/f6f72d4577/'+"?p="+ str(j)
    print(url)
    websiteData = getData(url)
    findEveryJpgUrl(websiteData, mangaUrlList)

    for singleUrl in mangaUrlList:
        webJpgData = getData(singleUrl)
        findMangaPage(webJpgData, mangaPageList)

    downloadManga(mangaPageList) 
