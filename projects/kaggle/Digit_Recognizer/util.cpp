#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

struct student {
    char name[20];
    int num;
    int age;
    char sex;
};

void testWriteTxt() {
    ofstream ofile("test.txt"); //追加和覆写？创建or打开？
    ofile << "hello, C++, world" << endl;
    ofile << "goodbye!" << endl;
    ofile.close();
}

void testReadTxt() {
    ifstream ifile("test.txt");
    if(!ifile.is_open()) {
        cout << "can't open this file";
        return ;
    }

    char buf[256];  //长度问题
    while(!ifile.eof()) {
        ifile.getline(buf, 256);
        cout << buf << endl;
    }
    //下面代码块的输出是什么？
//    for(int i = 0; i < sizeof buf; i ++){
//            cout <<buf[i]<< endl;
//    }
    ifile.close();
}

long getFileBytes(char* fileName) {
    long n;
    ifstream in(fileName, ios::in|ios::binary);
    in.tellg();
    in.seekg (0, ios::end);
    n = in.tellg();
    in.close();
    return n;
}


void testWriteBin() {
    student stud[3]= {"Li",1001,18,'f',"Fun",1002,19,'m',"Wang",1004,17,'f'};
    ofstream outfile("stud.dat",ios::binary);
    for(int i=0; i<3; i++)
        outfile.write((char*)&stud[i],sizeof(stud[i]));
    outfile.close( );
}

void testReadBin() {
    student stud[3];
    int i;
    ifstream infile("stud.dat",ios::binary);
    if(!infile) {
        cerr<<"open error!"<<endl;
        return ;
    }
    for(i=0; i<3; i++)
        infile.read((char*)&stud[i],sizeof(stud[i]));
    infile.close( );
    for(i=0; i<3; i++) {
        cout<<"NO."<<i+1<<endl;
        cout<<"name:"<<stud[i].name<<endl;
        cout<<"num:"<<stud[i].num<<endl;;
        cout<<"age:"<<stud[i].age<<endl;
        cout<<"sex:"<<stud[i].sex<<endl<<endl;
    }
}

int main() {
    testReadBin();
    return 0;
}


