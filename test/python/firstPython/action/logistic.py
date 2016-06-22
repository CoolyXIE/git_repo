from numpy import *

def loadDataSet(filePath):
    dataSet = []
    labelVec = []
    f = open(filePath)
    for line in f:
        lineArr = line.strip().split()
        dataSet.append([1.0, float(lineArr[0]), float(lineArr[1])])
        labelVec.append(int(lineArr[2]))
    return dataSet, labelVec

def sigmoid(inX):
    return 1.0/(1+exp(-inX))

def gradAscent(dataSet, labelVec):
    dataMat = mat(dataSet)
    labelMat = mat(labelVec).transpose()
    m, n = shape(dataMat)
    alpha = 0.001
    maxCycles = 500
    weights = ones((n,1))
    for i in range(maxCycles):
        h = sigmoid(dataMat * weights)
        err = labelMat - h
        weights = weights + alpha * dataMat.transpose() * err
    return weights

def plot(weights):
    import matplotlib.pyplot as plt
    w = weights.getA()
    dataSet, labelVec = loadDataSet('E:/data/python/Ch05/testSet.txt')
    dataArr = array(dataSet)
    n = shape(dataArr)[0]
    xcord1 = []
    xcord2 = []
    ycord1 = []
    ycord2 = []
    for i in range(n):
        if int(labelVec[i]) == 1:
            xcord1.append(dataArr[i, 1])
            ycord1.append(dataArr[i, 2])
        else:
            xcord2.append(dataArr[i, 1])
            ycord2.append(dataArr[i, 2])
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(xcord1, ycord1, s=30, c='red', marker='s')
    ax.scatter(xcord2, ycord2, s=30, c='green')
    x = arange(-3.0, 3.0, 0.1)
    y = (-w[0]-w[1]*x)/w[2]
    ax.plot(x,y)
    plt.xlabel('X1')
    plt.ylabel('X2')
    plt.show()


dataSet, labelVec = loadDataSet('E:/data/python/Ch05/testSet.txt')
plot(gradAscent(dataSet, labelVec))

