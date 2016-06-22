#ifndef DIRHELPER_H
#define DIRHELPER_H

#include <vector>
#include <iostream>
#include <io.h>
#include <string.h>

using namespace std;

class DirHelper
{
    public:
        DirHelper();
        DirHelper(string dir);
        virtual ~DirHelper();

        string getDirName();

        vector<string> getSpecFiles(string exd);
        vector<string> getIncludeFiles(bool includeDir = true);

    protected:


    private:
        string dirName;
};
void getRecursiveFiles(string dirPath, vector<string>& files);
#endif // DIRHELPER_H
