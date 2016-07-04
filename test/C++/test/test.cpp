#include <iostream>
#include "Triangle.h"
#include "Rectangle.h"

using namespace std;


void testOperaterOverload(){
//    测试重载操作符+和<<
    Rectangle rect1 = Rectangle(2,4);
    Rectangle rect2 = Rectangle(3,4);
    Rectangle rect3 = rect1+rect2;
    cout<< rect3;
}

void testPureVirtualFunc(){
//    纯虚函数不需要在基类实现，而虚函数需要在基类实现
    Rectangle rect = Rectangle(3.0, 4.0);
    Triangle tri = Triangle(1.0, 3.0, 2.5);
    cout << rect;
    cout << tri;
}

void testPointerOfPointer(){
    /* 用二维指针代替二维数组作为函数参数传递
    1.假定现在有一个二维数组，希望转化为指针的指针
    2.得到指针的指针后，知道数组大小，如何访问第(i,j)个元素
    */
    Rectangle r1 = Rectangle(1,1);
    Rectangle r2 = Rectangle(1,2);
    Rectangle r3 = Rectangle(2,1);
    Rectangle r4 = Rectangle(2,2);

    Rectangle **p; //定义指针的指针，一般得先有变量，再有指针
    //如何让p指向这四个数
    *p = &r1;
    *(*P+1) = r2;
    *()



}



int main(){

    return 0;
}
