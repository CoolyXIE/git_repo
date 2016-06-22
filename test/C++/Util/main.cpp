#include "CsvHelper.h"
#include "DirHelper.h"
#include "MyOpenCV.h"
#include "IOHelper.h"
#include "MyBoost.h"
#include "svm.h"
#include <stdlib.h>
#include <stdio.h>

#include <iterator>
#include <algorithm>
#include <boost/lambda/lambda.hpp>



void getFiles(string path, vector<string>& files) {
    //文件句柄
    long   hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            //如果是目录,迭代之
            //如果不是,加入列表
            if ((fileinfo.attrib &  _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            } else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

void testDirHelper() {
//    DirHelper dirHelper = DirHelper("C:\\Users\\Administrator\\Desktop");
    vector<string> files;
    getRecursiveFiles("C:\\Users\\Administrator\\Desktop", files);
    for(int i = 0; i < files.size(); i ++)
        cout <<  files[i] << endl;
}

void testCsvHelper() {
    CsvHelper csvHelper = CsvHelper("E:\\Workspace\\git_repo\\kaggle\\Digit_Recognizer\\data\\train_part.csv");

    for (int i = 1; i <= csvHelper.getCSVMap().size(); i ++) {
        vector<string> stringVec;
        csvHelper.getVecFromLine(2, stringVec);
        string path = "E:\\Workspace\\git_repo\\kaggle\\Digit_Recognizer\\data\\train_img\\";
        cout << i << endl;

        stringstream stream;
        stream << i;
        string num = stream.str();
        path.append(num);
        path.append(".txt");
        ofstream ofile(path);
        for(int i = 0; i < 28; i ++) {
            for (int j = 0; j < 28; j ++) {
                ofile << stringVec[i*28+j] << "\t";
            }
            ofile << endl;
        }
        ofile.close();
    }
}

void testBoost() {
    string line = "a\tb\tc\td";
    cout << line << endl;
    vector<string> result;
    MyBoost::split(line, result);
    for(int i = 0; i < result.size(); i ++) {
        cout << result[i] << endl;
    }
}



//void testSVM() {
//
//
//    struct svm_parameter param = {
//        .svm_type = C_SVC,
//        .kernel_type = RBF
//    };
//    struct svm_node x11 = {1, 0.1};
//    struct svm_node x12 = {2, 0.1};
//
//    struct svm_node x21 = {1, 0.1};
//    struct svm_node x22 = {2, 0.9};
//
//    struct svm_node x31 = {1, 0.9};
//    struct svm_node x32 = {2, 0.1};
//
//    struct svm_node x41 = {1, 0.9};
//    struct svm_node x42 = {2, 0.9};
//
//    struct svm_node x2[4][2] = {
//        x11,x12,x21,x22,x31,x32,x41,x42
//    };
//
//
//
//    struct svm_node **x;
//    x = new svm_node*[4];
//    for(int i = 0; i < 4; i ++){
//        x[i] = new svm_node[2];
//    }
//
//    **x = x11;
//    *(*x+1) = x12;
//    *(*(x+1)) = x21;
//    *(*(x+1)+1) = x22;
//    *(*(x+2)) = x31;
//    *(*(x+2)+1) = x32;
//    *(*(x+3)) = x41;
//    *(*(x+3)+1) = x42;
//
//    int l = 4;
//    double *y;
//    y = new double[4];
//    *y = 1;
//    *(y+1) = 2;
//    *(y+2) = 2;
//    *(y+3) = 1;
//
//    struct svm_problem problem = {
//        l, y, x
//    };
//    cout << "sf";
//    struct svm_model* model = svm_train(&problem, &param);
//
////    struct svm_node test1 = {1, 0.2};
////    struct svm_node test2 = {2, 0.2};
////    struct svm_node test0[2];
//
////    struct svm_node *test = (struct svm_node*)test0;
////    *test = test1;
////    *(test+1) = test2;
////    cout << svm_predict(model, test);
//}


int main() {
//    testSVM();
    return 0;
}
