#include <iostream>
#include <fstream>
#include "Classifer.h"
#include <vector>
#include <string>

using namespace std;

Classifer::Classifer()
{
    //ctor
}

Classifer::~Classifer()
{
    //dtor
}
vector<ImgArr> Classifer::loadTrainFile()
{
    ifstream ifile("data\train.csv");
    char buf[10000];//存储的buf。
    while(getline(buf,sizeof(buf)))//读取一行。
    {
        cout << "read line:" <<buf<<endl;//输出读取到的数据。
    }




    return vector<ImgArr>();
}


int Classifer::recognize(ImgArr imgArr,const int k)
{
    return 0;
}
