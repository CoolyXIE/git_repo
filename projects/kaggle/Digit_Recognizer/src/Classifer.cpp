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
    char buf[10000];//�洢��buf��
    while(getline(buf,sizeof(buf)))//��ȡһ�С�
    {
        cout << "read line:" <<buf<<endl;//�����ȡ�������ݡ�
    }




    return vector<ImgArr>();
}


int Classifer::recognize(ImgArr imgArr,const int k)
{
    return 0;
}
