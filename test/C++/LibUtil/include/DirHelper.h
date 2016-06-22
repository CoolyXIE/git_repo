#ifndef DIRHELPER_H
#define DIRHELPER_H
#include <string>
#include <vector>

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
        vector<string> getRecursiveFiles(bool includeDir = false);
    protected:


    private:
        string dirName;
};

#endif // DIRHELPER_H
