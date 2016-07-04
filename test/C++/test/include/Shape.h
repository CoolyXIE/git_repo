#ifndef SHAPE_H
#define SHAPE_H


class Shape {
public:
    Shape();
    virtual ~Shape();

    virtual double getCircum() = 0;
    virtual double getArea() = 0;

protected:

private:

};

#endif // SHAPE_H
