#include "DirHelper.h"
#include <iostream>
#include <io.h>
#include <vector>
#include <string.h>
DirHelper::DirHelper(){

    //ctor
}
DirHelper::DirHelper(string dir){
    this->dirName = dir;
}

DirHelper::~DirHelper(){
    //dtor
}

string DirHelper::getDirName(){
    return this->dirName;
}

vector<string> DirHelper::getSpecFiles(string exd){
    vector<string> files ;
    long   hFile   =   0;
    struct _finddata_t fileinfo;
    string exdName, pathName;
    string path = this->dirName;
    if (0 != strcmp(exd.c_str(), ""))
    {
        exdName = "\\*." + exd;
    }
    else
    {
        exdName = "\\*";
    }

    if((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));

        }
        while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }

    return files;
}

