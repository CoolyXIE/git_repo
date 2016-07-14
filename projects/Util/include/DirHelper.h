#ifndef DIRHELPER_H
#define DIRHELPER_H

#include <vector>
#include <iostream>
#include <io.h>
#include <string.h>

using namespace std;

class DirHelper{
    public:
        DirHelper(){};
        DirHelper(string dirPath);
        virtual ~DirHelper(){};

        string getDirPath();

        //得到文件夹下指定后缀名的所有文件名
        vector<string> getSpecFiles(string exd);
        //得到文件夹下所有的文件
        vector<string> getIncludeFiles(bool includeDir = true);
    private:
        string dirPath;
};


void getRecursiveFiles(string dirPath, vector<string>& files);
bool isDir(string filePath); //to-do


#endif // DIRHELPER_H
