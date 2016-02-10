# -*- coding:utf-8 -*-
'''
Created on 2016年1月28号

@author: xieke
'''
import random

from numpy import shape, mat, multiply, array, matrix, size, zeros


class svm(object):
    '''
    classdocs
    '''
    C = 0
    n = 0
    dataSet = []
    labelVec = []
    alpha = []
    u = []
    y = []
    
    def violateKKT(self, i):
        if (self.alpha[i] == 0 and self.y[i] * self.u[i] < 1)\
            or (self.alpha[i] == self.C and self.y[i] * self.u[i] > 1)\
            or ((self.alpha[i] > 0 and self.alpha[i] < self.C) \
                and self.C and self.y[i] * self.u[i] == 1):
            return False
        else:
            return True
    def __init__(self, filePath):
        '''
        Constructor
        '''
        f = open(filePath)
        for line in f:
            lineArr = line.strip().split('\t');
            self.dataSet.append([float(lineArr[0]), float(lineArr[1])])
            self.labelVec.append(int(lineArr[2]))
        f.close()
        self.y = self.labelVec
        
    def SMOSimple(self, C, toler, maxIter):
        dataMat = mat(self.dataSet);
        n = shape(dataMat)[0]
        b = 0
        alpha = zeros(n)
        iter = 0
        while(iter < maxIter):
            alphaPairs_changed = 0
            print 'iteration number: %d' %iter
            for i in range(n):
                x1 = dataMat[i]
                y1 = self.labelVec[i]
                prediction1 = float(mat(multiply(self.labelVec, alpha)) * kernel(dataMat, x1.T)) + b
                error1 = prediction1 - float(self.labelVec[i])
                if ((y1 * error1 < -toler) and alpha[i] < C) or ((y1 * error1 > toler) and alpha[i] > 0):
                    j = selectJrand(i, n)
                    x2 = dataMat[j]
                    y2 = self.labelVec[j]
                    prediction2 = float(mat(multiply(self.labelVec, alpha)) * kernel(dataMat, x2.T)) + b 
                    error2 = prediction2 - float(self.labelVec[j])
                    alpha1_old = alpha[i].copy()
                    alpha2_old = alpha[j].copy()
    # Step-1
                    if y1 != y2:
                        L = max(0, alpha[j] - alpha[i])
                        H = min(C, C + alpha[j] - alpha[i])
                    else:
                        L = max(0, alpha[j] + alpha[i] - C)
                        H = min(C, alpha[j] + alpha[i])
                    
                    if L == H:
                        print 'L = H'
                        continue
    # Step-2
                    eta = 2 * kernel(x1, x2.T) - kernel(x1, x1.T) - kernel(x2, x2.T);
                    if eta >= 0:
                        print 'eta >= 0', eta
                        continue
    # Step-3
                    alpha[j] -= y2 * (error1 - error2)/eta
    # Step-4
                    alpha[j] = fixAlpha(alpha[j], H, L)
                    if abs(alpha[j] - alpha2_old) < 0.00001:
#                         print 'j not moving enough'
                        continue
    # Step-5
                    alpha[i] += y2 * y1 * (alpha2_old - alpha[j])
                    b1 = b - error1 - y1 * (alpha[i] - alpha1_old) * kernel(x1, x1.T)\
                           - y2 * (alpha[j] - alpha2_old) * kernel(x1, x2.T)
                    b2 = b - error2 - y1 * (alpha[i] - alpha1_old) * kernel(x1, x2.T)\
                           - y2 * (alpha[j] - alpha2_old) * kernel(x2, x2.T)
                      
                    if alpha[i] > 0 and alpha[i] < C:
                        b = b1
                    elif alpha[j] > 0 and alpha[j] < C:
                        b = b2
                    else:
                        b = (b1 + b2)/2.0
                        
                    alphaPairs_changed += 1
                    print 'iter: %d i : %d, pairs changed %d' %(iter, i, alphaPairs_changed)
            if alphaPairs_changed == 0:
                iter += 1
            else:
                iter = 0
            
        return b, alpha
         
    def SMONormal(self, C, toler, maxIter):
        self.C = C
        dataMat = mat(self.dataSet);
        n = shape(dataMat)[0]; self.n = n
        b = 0
        self.u = zeros(n)
        self.alpha = zeros(n)
        alpha = self.alpha
        print self.u[0]
        prediction1 = self.u[0]
        prediction2 = self.u[1]
        iter = 0
        while(iter < maxIter):
            alphaPairs_changed = 0
            for i in range(n):
                print 'iteration number: %d' %iter
                if not self.violateKKT(i):
                    continue;
#                 j = self.heuristicFinder()
                j = selectJrand(i, n);
                
                x1 = dataMat[i]; x2 = dataMat[j]
                y1 = self.labelVec[i]; y2 = self.labelVec[j]
                prediction1 = float(mat(multiply(self.labelVec, alpha)) * kernel(dataMat, x1.T)) + b
                prediction2 = float(mat(multiply(self.labelVec, alpha)) * kernel(dataMat, x2.T)) + b 
                error1 = prediction1 - float(self.labelVec[i])
                error2 = prediction2 - float(self.labelVec[j])
                alpha1_old = alpha[i].copy()
                alpha2_old = alpha[j].copy()
                
                if y1 != y2:
                    L = max(0, alpha[j] - alpha[i])
                    H = min(C, C + alpha[j] - alpha[i])
                else:
                    L = max(0, alpha[j] + alpha[i] - C)
                    H = min(C, alpha[j] + alpha[i])
                        
                if L == H:
                    print 'L = H'
                    continue
                eta = 2 * kernel(x1, x2.T) - kernel(x1, x1.T) - kernel(x2, x2.T);
                if eta >= 0:
                    print 'eta >= 0', eta
                    continue
                
                alpha[j] -= y2 * (error1 - error2)/eta
                alpha[j] = fixAlpha(alpha[j], H, L)
                if abs(alpha[j] - alpha2_old) < 0.00001:
                    continue
                alpha[i] += y2 * y1 * (alpha2_old - alpha[j])
                
                b1 = b - error1 - y1 * (alpha[i] - alpha1_old) * kernel(x1, x1.T)\
                       - y2 * (alpha[j] - alpha2_old) * kernel(x1, x2.T)
                b2 = b - error2 - y1 * (alpha[i] - alpha1_old) * kernel(x1, x2.T)\
                       - y2 * (alpha[j] - alpha2_old) * kernel(x2, x2.T)
                if alpha[i] > 0 and alpha[i] < C:
                    b = b1
                elif alpha[j] > 0 and alpha[j] < C:
                    b = b2
                else:
                    b = (b1 + b2)/2.0
                alphaPairs_changed += 1
                print 'iter: %d i : %d, pairs changed %d' %(iter, i, alphaPairs_changed)
            if alphaPairs_changed == 0:
                iter += 1
            else:
                iter = 0
        return b, alpha     
    
def kernel(x1, x2):
    if shape(x1)[0] == 1:
        return float(x1 * x2)
    else:
        vec = []
        for i in range(shape(x1)[0]):
            vec.append(kernel(x1[i], x2))
        return mat(vec).T
     
def selectJrand(i , n):
    j = i
    while (j == i):
        j = int(random.uniform(0, n))
    return j


def fixAlpha(alpha2, H, L):
    if alpha2 > H:
        alpha2 = H  
    if L > alpha2:
        alpha2 = L
    return alpha2  
    
    
svm = svm("E:/data/python/Ch06/testSet.txt")
print svm.SMONormal(0.6, 0.001, 40)
# z = [[1, 2, 3], [4, 2, 3]]
# print(kernel(z,x))
#     matrix([[-3.88693126]])
