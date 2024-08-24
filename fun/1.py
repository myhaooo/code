# -*- coding: utf-8 -*-
from bs4 import BeautifulSoup
import io
import sys
import requests
hearders={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36 Edg/105.0.1343.53'}
#改变标准输出的默认编码
for name in range(29,999):
    st=''
    if name<10 :
        st="00"+str(name)
    elif name <100 :
        st="0"+str(name)
    else :
        st=str(name)
    url="https://scp-wiki-cn.wikidot.com/scp-"+st
    print(url)
    html=requests.get(url=url, headers=hearders).content.decode("utf-8")
    soup = BeautifulSoup(html,"html.parser")
    #print(soup)
    #print(soup.find_all('strong',string='项目编号'))

    s=str(soup)
    l1=s.find("<strong>")
    l2=s.find("footer",l1)
    print(l1)
    print(l2)
    lst=['<p>','</p>','<strong>','</strong>','<br/>','<blockquote>','<hr/>',"<li>",'</ul>','<ul>',"</li>"]
    s=s[l1:l2]
    for i in lst:
        s=s.replace(i,"")

    s=s.replace("&lt;","<")
    s=s.replace("&gt;",">")

    nm="scp-"+st+".txt"
    print(nm)
    with open(nm,'w',encoding='utf-8') as f:
        #print(s)
        f.write(s)
