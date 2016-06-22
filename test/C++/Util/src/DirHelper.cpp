#include "DirHelper.h"

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

vector<string> DirHelper::getIncludeFiles(bool includeDir){
    vector<string> files;
    long   hFile   =   0;
    struct _finddata_t fileinfo;
    string pathName;
    string path = this->dirName;
    string exdName = "\\*";
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

void getRecursiveFiles(string dirPath, vector<string>& files ){

    //文件句柄
    long   hFile   =   0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(dirPath).append("\\*").c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            //如果是目录,迭代之
            //如果不是,加入列表
            if((fileinfo.attrib &  _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                    getRecursiveFiles( p.assign(dirPath).append("\\").append(fileinfo.name), files );
            }
            else
            {
                files.push_back(p.assign(dirPath).append("\\").append(fileinfo.name) );
            }
        }while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
}
