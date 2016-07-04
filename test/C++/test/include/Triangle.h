#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include <Shape.h>
#include <vector>

using namespace std;

class Triangle : public Shape {
public:
    Triangle();
    Triangle(double a, double b, double c);
    virtual ~Triangle();

    vector<double> getEdges();
    double getCircum();
    double getArea();
    friend ostream& operator<<(ostream& output, Triangle& tri);

protected:

private:
    double e1;
    double e2;
    double e3;
};

#endif // TRIANGLE_H
