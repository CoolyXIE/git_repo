## -*- coding:utf-8 -*-
from nytimesarticle import *
import time
import os
def getArticles(desk, num, dirPath):
    dirPath = dirPath + "/" + desk
    key = '722ad8217eb4476c84430d35543e7755:5:74080153'
    api = articleAPI(key)
    list = []
    count = 1
    while len(list) < num:
        count += 1
        articles = api.search(q = desk.lower(), fq = {'news_desk': desk}, page=count)
        abstractList = parseAbstract(articles)
        list.extend(abstractList)
        print "\t",count,len(list)
        time.sleep(1)
    #写入文件
    if not os.path.exists(dirPath):
        os.mkdir(dirPath)
    for i in range(len(list)):
        filePath = dirPath + "/" + str(i) + ".txt"
        f = open(filePath, 'w')
        f.writelines(list[i])
        f.close()
    


def parseAbstract(articles):
    list = []
    for article in articles['response']['docs']:
        if article['abstract'] is not None:
            list.append(article['abstract'].encode("utf8"))
    return list

deskList = ["Education"]
for desk in deskList:
    print desk
    getArticles(desk, 20, "E:/data/nytimes")


##def parse(articles):
##    '''
##    This function takes in a response to the NYT api and parses
##    the articles into a list of dictionaries
##    '''
##    news = []
##    for i in articles['response']['docs']:
##        dic = {}
##        dic['id'] = i['_id']
##        if i['abstract'] is not None:
##            dic['abstract'] = i['abstract'].encode("utf8")
##        dic['headline'] = i['headline']['main'].encode("utf8")
##        dic['desk'] = i['news_desk']
####        dic['date'] = i['pub_date'][0:10] # cutting time of day.
##        dic['section'] = i['section_name']
##        if i['snippet'] is not None:
##            dic['snippet'] = i['snippet'].encode("utf8")
##        dic['source'] = i['source']
##        dic['type'] = i['type_of_material']
##        dic['url'] = i['web_url']
##        dic['word_count'] = i['word_count']
##        # locations
##        locations = []
##        for x in range(0,len(i['keywords'])):
##            if 'glocations' in i['keywords'][x]['name']:
##                locations.append(i['keywords'][x]['value'])
##        dic['locations'] = locations
##        # subject
##        subjects = []
##        for x in range(0,len(i['keywords'])):
##            if 'subject' in i['keywords'][x]['name']:
##                subjects.append(i['keywords'][x]['value'])
##        dic['subjects'] = subjects   
##        news.append(dic)
##    return(news)
