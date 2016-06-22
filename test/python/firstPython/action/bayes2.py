# -*- coding: utf-8 -*-
from numpy import *

def bayesClaasifier(vec, p0Vec, p1Vec, pClass1):
    p1 = sum(vec * p1Vec) + log(pClass1)
    p0 = sum(vec * p0Vec) + log(1.0 - pClass1)
    if p1 > p0:
        return 1
    else:
        return 0

def bayesTrainer(trainMatrix, trainCategory):
    num = len(trainMatrix)
    numWords = len(trainMatrix[0])
    prob = sum(trainCategory)/float(num) #trainCategory为0,1向量
    p0Num = ones(numWords)
    p1Num = ones(numWords)
    p0Denom = 2.0
    p1Denom = 2.0
    for i in range(num):
        if trainCategory[i] == 1:
            p1Num += trainMatrix[i]
            p1Denom += sum(trainMatrix[i])
        else:
            p0Num += trainMatrix[i]
            p0Denom += sum(trainMatrix[i])

    p1Vect = log(p1Num/p1Denom)
    p0Vect = log(p0Num/p0Denom)
    return p0Vect, p1Vect, prob


def loadDataSet():
    postingList=[['my', 'dog', 'has', 'flea', 'problems', 'help', 'please'],
                 ['maybe', 'not', 'take', 'him', 'to', 'dog', 'park', 'stupid'],
                 ['my', 'dalmation', 'is', 'so', 'cute', 'I', 'love', 'him'],
                 ['stop', 'posting', 'stupid', 'worthless', 'garbage'],
                 ['mr', 'licks', 'ate', 'my', 'steak', 'how', 'to', 'stop', 'him'],
                 ['quit', 'buying', 'worthless', 'dog', 'food', 'stupid']]
    classVec = [0,1,0,1,0,1]    #1 is abusive, 0 not
    return postingList,classVec

def createVocabList(dataSet):
    vocabSet = set([])
    for document in dataSet:
        vocabSet = vocabSet | set(document)
    return list(vocabSet)

def setOfWords2Vec(vocabList, inputSet):
    returnVec = [0] * len(vocabList)
    for word in inputSet:
        if word in vocabList:
            returnVec[vocabList.index(word)] = 1
    return returnVec


            


dataSet, labels = loadDataSet()
myVocabList = createVocabList(dataSet)
trainMat =[]
for postinDoc in dataSet:
    trainMat.append(setOfWords2Vec(myVocabList, postinDoc))
p0Vect, p1Vect, prob = bayesTrainer(trainMat, labels)






