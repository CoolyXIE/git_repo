from math import log
from numpy import argsort
def create_decision_tree(dataSet):
    baseEntropy = cal_Shannon_entropy(dataSet)
    if baseEntropy == 0:
        return dataSet[0][-1]
    entropList = []
    for index in range(len(dataSet[0])-1):
        entropy = entropy_after_split(dataSet, index)
        entropList.append(entropy)
    bestIndex = argsort(entropList)[0]
    attributeSet = set()
    for row in dataSet:
        attributeSet.add(row[bestIndex])    
    tree = {}
    for attribute in attributeSet:
        sub_dataSet = split_dataSet(dataSet, bestIndex, attribute)
        sub_tree = create_decision_tree(sub_dataSet)
        tree[attribute] = sub_tree
    return tree

def cal_Shannon_entropy(dataSet):
    total = len(dataSet)
    label_counter ={}
    for row in dataSet:
        label = row[-1]
        count = 1
        if label in label_counter.keys():
            count = label_counter[label] + 1
        label_counter[label] = count
    shannon_entropy = 0.0
    for key in label_counter:
        prob = 1.0 * label_counter[key] / total
        shannon_entropy -= prob * log(prob, 2)
    return shannon_entropy

def entropy_after_split(dataSet, col_index):
    attribute_counter = {}
    total_entropy = 0.0
    for row_num in range(len(dataSet)):
        attribute = dataSet[row_num][col_index]
        count = 1
        if attribute in attribute_counter.keys():
            count = attribute_counter[attribute] + 1
        attribute_counter[attribute] = count
        prob = 1.0 * attribute_counter[attribute] / len(dataSet)

        total_entropy = prob * cal_Shannon_entropy(split_dataSet(dataSet, col_index, attribute))
    return total_entropy


def split_dataSet(dataSet, col_index, attribute):
    sub_dataSet = []
    for feature_vec in dataSet:
        if feature_vec[col_index] == attribute:
            sub_feature_vec = feature_vec[:col_index]
            sub_feature_vec.extend(feature_vec[col_index+1:])
            sub_dataSet.append(sub_feature_vec)
    return sub_dataSet

def file_to_dataSet(filePath):
    dataSet = []
    f = open(filePath)
    for line in f:
        features = line.strip().split('\t')
        dataSet.append(features)
    return dataSet

dir = 'E:/data/python/Ch03/'
dataSet = file_to_dataSet(dir+'lenses.txt')
result = create_decision_tree(dataSet)

##print base_entropy
##print entropy_after_split(dataSet, 0)

