#include <iostream>

using namespace std;
// Base class
class Shape {

public:
    void setWidth(int w) {
        width = w;
    }

    void setHeight(int h) {
        height = h;
    }

protected:
    int width;
    int height;
};
// Derived class
// 派生类会继承基类的所有方法，除了：构造函数、析构函数、拷贝构造函数、重载操作符和友元函数
// 继承语法： class <derived-class>:access baseA, access baseB...
class Rectangle: public Shape {
public:
    int getArea() {
        return (width * height);
    }
};


























int main(void) {
    Rectangle Rect;

    Rect.setWidth(5);
    Rect.setHeight(7);

    // Print the area of the object.
    cout << "Total area: " << Rect.getArea() << endl;

    return 0;
}
