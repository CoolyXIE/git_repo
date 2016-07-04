#include "Triangle.h"
#include <math.h>

using namespace std;

Triangle::Triangle()
{
    //ctor
}

Triangle::Triangle(double a, double b, double c){
    this->e1 = a;
    this->e2 = b;
    this->e3 = c;
}

Triangle::~Triangle()
{
    //dtor
}

vector<double> Triangle::getEdges(){
    vector<double> edges;
    edges.push_back(this->e1);
    edges.push_back(this->e2);
    edges.push_back(this->e3);
    return edges;
}

double Triangle::getCircum(){
    return e1 + e2 + e3;
}

ostream& operator<<(ostream& output, Triangle& tri){
    vector<double> edges = tri.getEdges();
    output << "e1: " << edges[0] << ", e2: " << edges[1] << ", e3: " << edges[2] << "\t";
    output << "Area: " << tri.getArea() << ", Circum: " << tri.getCircum() << endl;
    return output;
}

double Triangle::getArea(){
    double p = 0.5 * getCircum();
    return sqrt(p * (p-e1) * (p-e2) * (p-e3));
}
