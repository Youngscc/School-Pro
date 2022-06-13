# -*- coding: UTF-8 -*-
from bs4 import BeautifulSoup
import requests
import lxml
import sys
import pymysql
import re


# --------set page amount----------

def set_download_urls():
    baseUrl = 'https://internet.cnmo.com/tech/'
    retUrl = []
    for i in range(1, 21):
        retUrl.append(baseUrl  + str(i) + '/')
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
        ret.append(table_bf.find('div', class_="listbox"))
    return ret


#

# ---------get article links------------
def get_download_url():
    downloadTables = get_download_tables()
    # a = open("hahaha.txt", "w")
    articles = []
    for each in downloadTables:
        text = each.find_all('div', class_='txtbox')
        for item in text:
            articles.append(item.find('a'))
    return articles


def read_article_info():
    articles = get_download_url()
    dict = {}
    idx = 0
    for item in articles:
        if item is not None:
            dict['科技' + str(idx)] = 'https:'+item.get('href')
            idx = idx + 1
    return dict


# ---------get content info and save ---------------

def correct_title(title):
    invalid_chars = '[\\\/:*?"<>|]'
    replace_char = '-'
    return re.sub(invalid_chars, replace_char, title)


def get_content(title, url):
    print(title + '---->' + url)
    req = requests.get(url)
    req.encoding = 'gb2312'
    html = req.text
    table_bf = BeautifulSoup(html, features='lxml')
    if table_bf.find('div', class_="ctitle") is None:
        return
    main = table_bf.find('div', class_="ctitle").find('h1').get_text()
    article = table_bf.find('div', class_="ctext")
    content = article.find_all("p", style=None)
    text = ""
    #
    # print(main)
    for item in content:
        text += item.get_text()
        text += "\n"
    a = open("../article/" + correct_title(title+ '_'+ main + ".txt"), "w")
    print(text, file=a)


# --------save all article -----------

def save_data():
    dict = read_article_info()
    for key, value in dict.items():
        get_content(key, value)
        # print(key, value, file=a)


save_data()
