#include <iostream>
#include "Triangle.h"
#include "Rectangle.h"

using namespace std;


void testOperaterOverload(){
//    �������ز�����+��<<
    Rectangle rect1 = Rectangle(2,4);
    Rectangle rect2 = Rectangle(3,4);
    Rectangle rect3 = rect1+rect2;
    cout<< rect3;
}

void testPureVirtualFunc(){
//    ���麯������Ҫ�ڻ���ʵ�֣����麯����Ҫ�ڻ���ʵ��
    Rectangle rect = Rectangle(3.0, 4.0);
    Triangle tri = Triangle(1.0, 3.0, 2.5);
    cout << rect;
    cout << tri;
}

void testPointerOfPointer(){
    /* �ö�άָ������ά������Ϊ������������
    1.�ٶ�������һ����ά���飬ϣ��ת��Ϊָ���ָ��
    2.�õ�ָ���ָ���֪�������С����η��ʵ�(i,j)��Ԫ��
    */
    Rectangle r1 = Rectangle(1,1);
    Rectangle r2 = Rectangle(1,2);
    Rectangle r3 = Rectangle(2,1);
    Rectangle r4 = Rectangle(2,2);

    Rectangle **p; //����ָ���ָ�룬һ������б���������ָ��
    //�����pָ�����ĸ���
    *p = &r1;
    *(*P+1) = r2;
    *()



}



int main(){

    return 0;
}
