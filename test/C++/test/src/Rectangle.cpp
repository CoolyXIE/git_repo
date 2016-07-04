#include "Rectangle.h"

Rectangle::Rectangle() {
    this->width = 0;
    this->height = 0;
}

Rectangle::Rectangle(double width, double height) {
    this->width = width;
    this->height = height;
}

Rectangle::~Rectangle() {
    //dtor
}

double Rectangle::getWidth() const {
    return this->width;
}

double Rectangle::getHeight() const {
    return this->height;
}

double Rectangle::getArea(){
    return this->width * this->height;
}

double Rectangle::getCircum(){
    return 2*(this->width + this->height);
}

Rectangle Rectangle::operator+(const Rectangle& rect) {
    double width_out = 0;
    double height_out = 0;

    if (rect.getWidth() == this->width) {
        width_out = this->width;
        height_out = this->height + rect.getHeight();
    } else if(rect.getHeight() == this->height) {
        width_out = this->width + rect.getWidth();
        height_out = this->height;
    }

    return Rectangle(width_out, height_out);
}

ostream& operator<<(ostream& output, Rectangle& rect){
    output << "Width: " << rect.getWidth() << ", Height: " << rect.getHeight() << "\t";
    output << "Area: " << rect.getArea() << ", Circum: " << rect.getCircum() << endl;
    return output;
}








