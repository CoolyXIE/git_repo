#include <iostream>

using namespace std;

class Shape{
//    Shape可以有周长,面积
private:
    double circum;
    double area;

public:
    Shape(double circum, double area);
    double getCircum();
    double getArea();
};

class Rectangle: public Shape{
private:
    double width;
    double height;

public:
    Rectangle(double width, double height);
    double getWidth();
    double getHeight();
    Rectangle operator+(const Rectangle& rect){
        double width_out;
        double height_out;

        if (rect.getWidth() == this->width){
            width_out =
        }


        double width2 = rect.getWidth();
        double height1 = this->height;
        double height2 = rect.getHeight();

    }


};

class Square: public Rectangle{
};

void testOperaterOverload(){



}


int main(){

}
