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

        //�õ��ļ�����ָ����׺���������ļ���
        vector<string> getSpecFiles(string exd);
        //�õ��ļ��������е��ļ�
        vector<string> getIncludeFiles(bool includeDir = true);
    private:
        string dirPath;
};


void getRecursiveFiles(string dirPath, vector<string>& files);
bool isDir(string filePath); //to-do


#endif // DIRHELPER_H
