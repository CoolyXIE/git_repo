#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>

#include "DirHelper.h"
#include "CsvHelper.h"

using namespace std;

void testDirHelper() {
    DirHelper dirHelper = DirHelper("C:\\Users\\Administrator\\Desktop");
    vector<string> files = dirHelper.getSpecFiles("jpg");
    for(size_t i = 0; i < files.size(); i ++)
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

int main() {
    testCsvHelper();
    return 0;
}
