# -*- coding:utf-8 -*-
from numpy import *
import os
import sys

#将文章转化为单词列表
def format2WordList(filePath):
    wordList = []
    f = open(filePath)
    for line in f:
        words = line.strip().split(' ')
        for word in words:
        #现在粗暴地将不是字母的单词全部过滤掉,且长度至少为3
            if word.isalpha() and len(word)>=3:
                wordList.append(word)
    return wordList

#给出训练集文件目录，转化为dataSet和labels
def format2dataSet(dataDir):
    listDirs = os.listdir(dataDir)
    dataSet = []
    labels = []
    for dirName in listDirs:
        dirPath = dataDir + '/' + dirName
        if os.path.isdir(dirPath):
            listFiles = os.listdir(dirPath)
            for fileName in listFiles:
                filePath = dirPath + '/' + fileName
                wordVec = format2WordList(filePath)
                if dirName in wordVec:
                    wordVec.remove(dirName)
                dataSet.append(wordVec)
                labels.append(dirName)
    return dataSet, labels

#训练
def training(dataSet, labels, wordSetDict):
    resultDict = {}
    labelDict ={}
    #init
    for label in set(labels):
        resultDict[label] = {}
        labelDict[label] = 0
    #counter
    for i in range(len(labels)):
        wordList = dataSet[i]
        label = labels[i]
        labelDict[label] += 1 
        result = resultDict[label]
        for word in wordList:
            count = 1
            if word in result.keys():
                count = result[word] + 1
            result[word] = count
    #cal prob
    for label in resultDict.keys():
        labelDict[label] = log(1.0 * labelDict[label] / len(dataSet))
        totalSize = len(wordSetDict[label])
        for word in resultDict[label].keys():
            prob = log(1.0 * resultDict[label][word] / totalSize)
            resultDict[label][word] = prob
    
    return resultDict, labelDict

def classify(wordList, resultDict, labelDict, wordSetDict):
    probVec = []
    maxLen = 0
    for label in wordSetDict.keys():
        if len(wordSetDict[label]) > maxLen:
            maxLen = len(wordSetDict[label])
    notFoundWordProb = log(0.5 / maxLen)
    for label in labelDict.keys():
##        print '-------',label,'---------'
        labelProb = labelDict[label]
        wordProbSum = 0
        for word in wordList:
            if word in resultDict[label].keys():
                wordProb = resultDict[label][word]
            else:
##                print 'not found',
                wordProb = notFoundWordProb
##            print word,':',wordProb
            wordProbSum += wordProb
##        print 'word sum prob:',wordProbSum
##        print 'label prob:', labelProb
        prob = labelProb + wordProbSum
##        print 'sum:', prob
        probVec.append(prob)
    bestIndex = argsort(probVec)[-1]
    bestLabel = labelDict.keys()[bestIndex]
##    print 'best',bestLabel,'prob',probVec[bestIndex],'index',bestIndex
##    print 'other ham','prob',probVec[0]
    return bestLabel
    

#对于每一个label生成词集
def generate_wordSetDict(dataSet, labels):
    wordSetDict = {}
    length = len(labels)
    for i in range(length):
        wordSet = set(dataSet[i])
        if labels[i] in wordSetDict.keys():
            wordSet = wordSetDict[labels[i]].union(wordSet)
        wordSetDict[labels[i]] = wordSet
    return wordSetDict

#实用词袋模型，对于每一个label生成词袋
def generate_wordBagDict(dataSet, labels):
    wordBagDict = {}
    length = len(labels)
    for i in range(length):
        wordBag ={}
        for word in dataSet[i]:
            count = 1
            if word in wordBag.keys():
                count = wordBag[word] + 1
            wordBag[word] = count
        if labels[i] in wordBagDict.keys():
            oldWordBag = wordBagDict[labels[i]]
            for oldWord in oldWordBag.keys():
                oldCount = oldWordBag[oldWord]
                newCount = 0
                if oldWord in wordBag.keys():
                    newCount = wordBag[oldWord]
                wordBag[oldWord] = oldCount + newCount
        wordBagDict[labels[i]] = wordBag
    return wordBagDict
        


dataDir = "E:/data/nytimes"
dataSet, labels = format2dataSet(dataDir)
wordSetDict = generate_wordSetDict(dataSet, labels)
resultDict, labelDict = training(dataSet, labels, wordSetDict)

#test
wordList = format2WordList(dataDir + "/test.txt")
print wordList
print classify(wordList, resultDict, labelDict, wordSetDict)











