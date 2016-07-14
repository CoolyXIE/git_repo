#include "CsvHelper.h"
#include "DirHelper.h"
#include "MyBoost.h"
#include <stdlib.h>
#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <ostream>
#include <boost/lambda/lambda.hpp>

using namespace std;

void getFiles(string path, vector<string>& files) {
    //�ļ����
    long   hFile = 0;
    //�ļ���Ϣ
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            //�����Ŀ¼,����֮
            //�������,�����б�
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
//    CsvHelper csvHelper = CsvHelper("E:\\Workspace\\git_repo\\kaggle\\Digit_Recognizer\\data\\train_part.csv");
//    for (int i = 1; i <= csvHelper.getCSVMap().size(); i ++) {
//        vector<string> stringVec;
//        csvHelper.getVecAtLine(2, stringVec);
//        string path = "E:\\Workspace\\git_repo\\kaggle\\Digit_Recognizer\\data\\train_img\\";
//        cout << i << endl;
//        stringstream stream;
//        stream << i;
//        string num = stream.str();
//        path.append(num);
//        path.append(".txt");
//        ofstream ofile(path);
//        for(int i = 0; i < 28; i ++) {
//            for (int j = 0; j < 28; j ++) {
//                ofile << stringVec[i*28+j] << "\t";
//            }
//            ofile << endl;
//        }
//        ofile.close();
//    }
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

int main() {
    return 0;
}
