//#ifndef SHAPE_H
//#define SHAPE_H
//#include <core.hpp>
//
//using namespace cv;
//using namespace std;
//
////util
//double calAngleInArc(Point2f left, Point2f vertex, Point2f right);
//double arc2Degree(double angleInArc);
//
//class Shape{
//    public:
//        Shape(){};
//        virtual ~Shape(){};
//
//        virtual double getCircum() = 0;
//        virtual double getArea() = 0;
//        virtual Mat draw() = 0;
//
//    protected:
//
//    private:
//};
//
//class Line{
//public:
//    Point2f p1;
//    Point2f p2;
//
//    Line(Point2f beginPoint, Point2f endPoint);
//    double getLength();
//    double getTheta();
//
//    friend ostream &operator<<(ostream &os, const Line &line);
//};
//
//class Circle : Shape{
//public:
//    Point2f center;
//    double radius;
//
//    Circle(Point2f center, double radius);
//
//    double getArea();
//    double getCircum();
//
//    friend ostream &operator<<(ostream &os, const Circle &circle);
//};
//
//class Polygon : Shape{
//public:
//    int n;
//    vector<Point2f> vertices;
//
//    Polygon(vector<Point2f> vertices);
//
//    //得到多边形的点、边、角(按顺序)
//    vector<Point2f> &getVertices();
//    vector<double> getEdges();
//    vector<double> getAngles();
//
//    double getArea();
//    double getCircum();
//
//    virtual bool check() = 0;
//
//    friend ostream &operator<<(ostream &os, const Polygon &polygon);
//};
//
//class Triangle : Polygon{
//public:
//    Triangle(vector<Point2f> &vertices);
//    bool check();
//};
//
//class Parallelogram : Polygon{
//public:
//    Parallelogram(vector<Point2f> &vertices);
//    bool check();
//};
//
////class Rhombus : Parallelogram{
////public:
////    Rhombus(vector<Point2f> &vertices);
////
////    bool check();
////};
//
//class Rectangle : Parallelogram{
//public:
//    Rectangle(vector<Point2f> &vertices);
//    bool check();
//};
//
//class Square : Rectangle{
//public:
//    Square(vector<Point2f> &vertices);
//    bool check();
//};
//
//
//
//
//#endif // SHAPE_H
