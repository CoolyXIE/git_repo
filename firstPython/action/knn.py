from numpy import *


def classify_knn(inX, dataSet, labels, k):
    size = dataSet.shape[0]
    diffMat = tile(inX, (size, 1)) - dataSet
    distances = (diffMat**2).sum(axis=1)**0.5
    sorted_index = distances.argsort()
    counter = {}
    for i in range(k):
        label = labels[sorted_index[i]]
        counter[label] = counter.get(label, 0) + 1
    sorted_counter = sorted(counter.items(), key = lambda counter:counter[1], reverse=True)
    return sorted_counter[0][0]


def file2Matrix(fileName):
    dict = {'largeDoses':1,'smallDoses':2, 'didntLike':3}
    dataSet = array([0.0,0.0,0.0])
    labels = []
    f = open(fileName)
    for line in f:
        row = line.split('\t')
        label = row.pop(-1).strip()
        for i in range(len(row)):
            row[i] = float(row[i])
        dataSet = vstack((dataSet, row))
        labels.append(dict[label])
    dataSet = dataSet[1:]
    return dataSet,labels

def auto_normalize(dataSet):
    ranges = []
    minVals = []
    for i in range(dataSet.shape[1]):
        minVal = min(dataSet[:,i])
        maxVal = max(dataSet[:,i])
        minVals.append(minVal)
        ranges.append(maxVal - minVal)
        dataSet[:,i] = (dataSet[:,i] - minVal)/(maxVal - minVal)
    return ranges,minVals

def split_train_test(fileName, outputDir):
    import random
    input = open(fileName)
    output_train = open(outputDir + "train.txt",'w')
    output_test = open(outputDir + "test.txt", 'w')
    for line in input:
        if random.random() > 0.1:
            output_train.writelines(line)
        else:
            output_test.writelines(line)
    input.close()
    output_train.close()
    output_test.close()

def test(k):
    train_file = 'C:/Users/xieke.LITB-INC/Desktop/python/code/Ch02/train.txt'
    test_file = 'C:/Users/xieke.LITB-INC/Desktop/python/code/Ch02/test.txt'
    dataSet,labels = file2Matrix(train_file)
    test_dataSet, test_labels = file2Matrix(test_file)
    auto_normalize(dataSet)
    auto_normalize(test_dataSet)
    
    total = len(test_labels)
    err = 0
    for index in range(total):
        inX = test_dataSet[index, :].tolist()
        result_label = classify_knn(inX, dataSet, labels, k)
        if result_label != test_labels[index]:
            err += 1
    return 1.0*err/total

err = []
for k in range(3,100):
    err.append(test(k))
index = argsort(err)[0]+3
print index, err[index]


##dir = 'C:/Users/xieke.LITB-INC/Desktop/python/code/Ch02'
##split_train_test(dir + "/datingTestSet.txt", dir)

##dataSet,labels = file2Matrix("C:/Users/xieke.LITB-INC/Desktop/python/code/Ch02/datingTestSet.txt")
##print dataSet[1:12,:]
##auto_normalize(dataSet)
##print dataSet[1:12,:]
##dataSet.min(0)
##import matplotlib
##import matplotlib.pyplot as plt
##fig = plt.figure()
##ax = fig.add_subplot(111)
##ax.scatter(dataSet[:,0],dataSet[:,2], 15.0*array(labels), 15.0*array(labels))
##plt.show()

##norm_matrix, ranges, minVals = auto_normalize(dataSet)







##train_file = 'C:/Users/xieke.LITB-INC/Desktop/python/code/Ch02/train.txt'
##dataSet,labels = file2Matrix(train_file)
##
##
##from pylab import *
##import matplotlib.pyplot as plt
##fig = plt.figure()
##ax = fig.add_subplot(111, projection='3d')
##color_dict={1:'y',2:'r',3:'g'}
####for i in range(len(labels)):
####    x = dataSet[i][0]
####    y = dataSet[i][1]
####    z = dataSet[i][2]
####    ax.scatter(x,y,z,c=color_dict[labels[i]])
##
##plt.show()
























    


