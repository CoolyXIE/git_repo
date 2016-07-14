#ifndef SHAPE_H
#define SHAPE_H

#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include <vector>
#include <map>

using namespace std;
using namespace cv;

const double pi = 3.1415926;

class MyPoint2f{
public:
    MyPoint2f(){};
    MyPoint2f(float x, float y);
    float x;
    float y;
    double getModule() const;
    bool operator<(const MyPoint2f &) const;
};

class Shape{
    public:
        Shape(){};
        virtual ~Shape(){};
};

class Line{
public:
    //构造函数
	Line(Point2f beginPoint, Point2f endPoint);

    //成员变量
	Point2f beginPoint;
	Point2f endPoint;
    float k;
    float b;

    //公用方法
    bool isOnLine(Point2f p, double eps = 1e-8);
    bool isOnSameSide(Point2f p1, Point2f p2);

    //重载
    friend ostream &operator<<(ostream &os, const Line &l);
};

class Ellipse{
public:
    //构造函数
    Ellipse(Point2f leftUp, Point2f rightDown);

    //成员变量
    Point2f center;
    double a;
    double b;
    int longAxisTheta; //只考虑0和90度

    //公用方法
    bool isEmpty();
    bool contains(Point2f pt);
    Mat drawOnImg(Mat &img);

    //重载
    friend ostream &operator<<(ostream &os, const Ellipse &e);
};

class Circle{
public:
    //构造函数
	Circle(Point2f center, float radius);

	//成员变量
    Point2f center;
	float radius;

	//公用方法
    vector<Point> getContourPoints();
    Mat drawOnImg(Mat &img); //to-do

    //重载
	friend ostream &operator<<(ostream &os, const Circle &c);
};

class Rectangle{
public:
    //构造函数
    Rectangle(){};
	Rectangle(vector<Point2f> &points);
	Rectangle(Rect &rect);

	//成员变量
	vector<Point2f> points;

    //公用方法
    double getArea();
	double getMaxEdgeLen();
	Mat drawOnImg(Mat &img, string title="矩形");

    //重载
	friend ostream &operator<<(ostream &os, const Rectangle &r);
};

class Polygon{
public:
    //构造函数
    Polygon(vector<Point2f> &points);

	//成员变量
	int sides;
	vector<Point2f> points;

    //公用方法
    double getArea();
	double getMaxEdge();
	double getMinEdge();
    vector<Point2f> &getAllPoints();
	vector<double> getAllEdges();
	vector<double> getAllAngles();
    vector<Point2f> getIncludePixelsOfImg(Mat &img);
    Mat getIncludeImg(Mat &img);
    Mat drawOnImg(Mat &img, string title="多边形");
    bool contains(Point2f pt);
    bool contains(Point pt);

    //重载
	friend ostream &operator<<(ostream &os, const Polygon &p);


};

//util
double calAngleInDegree(Point2f left, Point2f center, Point2f right);
double calCosine(double angleInDegree);
double angleInDegree2Arc(double angleInDegree);
double angleInArc2Degree(double angleInArc);

#endif // SHAPE_H
