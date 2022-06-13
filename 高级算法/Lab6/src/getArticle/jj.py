# -*- coding: UTF-8 -*-
from bs4 import BeautifulSoup
import requests
import lxml
import sys
import pymysql
import re


# --------set page amount----------

def set_download_urls():
    baseUrl = 'http://finance.ce.cn/2015home/jj/index'
    retUrl = [baseUrl + '.shtml']
    for i in range(1, 10):
        retUrl.append(baseUrl + '_' + str(i) + '.shtml')
    return retUrl


# --------get download page urls

def get_download_tables():
    pageUrl = set_download_urls()
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome / 46.0.2490.80Safari / 537.36',
        'Content-Type': 'text/html',
    }
    ret = []
    for url in pageUrl:
        req = requests.get(url, headers=headers)
        req.encoding = 'gb2312'
        html = req.text
        table_bf = BeautifulSoup(html, features="html.parser")
        ret.append(table_bf.find('table', width="100%", border="0", cellpadding="0"))
    return ret


#

# ---------get article links------------
def get_download_url():
    downloadTables = get_download_tables()

    articles = []
    for each in downloadTables:
        text = each.find_all('tr')
        for item in text:
            articles.append(item.find('a'))
    return articles


def read_article_info():
    articles = get_download_url()
    baseUrl = 'http://finance.ce.cn/'
    dict = {}
    idx = 0
    for item in articles:
        if item is not None:
            dict['经济' + str(idx)] = item.get('href').replace("../../", baseUrl)
            idx = idx + 1
    return dict


# ---------get content info and save ---------------

def correct_title(title):
    invalid_chars = '[\\\/:*?"<>|]'
    replace_char = '-'
    return re.sub(invalid_chars, replace_char, title)


def get_content(title, url):
    print(title + '---->' + url)
    if url.find('shtml') == -1:
        return
    req = requests.get(url)
    req.encoding = 'gb2312'
    html = req.text
    table_bf = BeautifulSoup(html, features='lxml')
    main = table_bf.find('h1', id="articleTitle").get_text()
    article = table_bf.find('div', class_="TRS_Editor")
    content = article.find_all("p")
    text = ""
    #
    # print(main[9:])
    for item in content:
        text += item.get_text()
        text += "\n"
    a = open("../article/" + correct_title(title + '_' + main[9:] + ".txt").replace('\n', "").replace(' ', ""), "w")
    print(text, file=a)


# --------save all article -----------

def save_data():
    dict = read_article_info()
    a = open("hahaha.txt", 'w')
    for key, value in dict.items():
        get_content(key, value)


save_data()
