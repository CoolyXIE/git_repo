#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <iostream>
#include <Shape.h>

using namespace std;


class Rectangle : public Shape {
public:
    Rectangle();
    Rectangle(double width, double height);
    virtual ~Rectangle();


    double getWidth() const;
    double getHeight() const;
    double getArea();
    double getCircum();

    Rectangle operator+(const Rectangle& rect);
    friend ostream& operator<<(ostream& output, Rectangle& rect);

protected:

private:
    double width;
    double height;
};

#endif // RECTANGLE_H
