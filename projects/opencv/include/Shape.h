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
    //���캯��
	Line(Point2f beginPoint, Point2f endPoint);

    //��Ա����
	Point2f beginPoint;
	Point2f endPoint;
    float k;
    float b;

    //���÷���
    bool isOnLine(Point2f p, double eps = 1e-8);
    bool isOnSameSide(Point2f p1, Point2f p2);

    //����
    friend ostream &operator<<(ostream &os, const Line &l);
};

class Ellipse{
public:
    //���캯��
    Ellipse(Point2f leftUp, Point2f rightDown);

    //��Ա����
    Point2f center;
    double a;
    double b;
    int longAxisTheta; //ֻ����0��90��

    //���÷���
    bool isEmpty();
    bool contains(Point2f pt);
    Mat drawOnImg(Mat &img);

    //����
    friend ostream &operator<<(ostream &os, const Ellipse &e);
};

class Circle{
public:
    //���캯��
	Circle(Point2f center, float radius);

	//��Ա����
    Point2f center;
	float radius;

	//���÷���
    vector<Point> getContourPoints();
    Mat drawOnImg(Mat &img); //to-do

    //����
	friend ostream &operator<<(ostream &os, const Circle &c);
};

class Rectangle{
public:
    //���캯��
    Rectangle(){};
	Rectangle(vector<Point2f> &points);
	Rectangle(Rect &rect);

	//��Ա����
	vector<Point2f> points;

    //���÷���
    double getArea();
	double getMaxEdgeLen();
	Mat drawOnImg(Mat &img, string title="����");

    //����
	friend ostream &operator<<(ostream &os, const Rectangle &r);
};

class Polygon{
public:
    //���캯��
    Polygon(vector<Point2f> &points);

	//��Ա����
	int sides;
	vector<Point2f> points;

    //���÷���
    double getArea();
	double getMaxEdge();
	double getMinEdge();
    vector<Point2f> &getAllPoints();
	vector<double> getAllEdges();
	vector<double> getAllAngles();
    vector<Point2f> getIncludePixelsOfImg(Mat &img);
    Mat getIncludeImg(Mat &img);
    Mat drawOnImg(Mat &img, string title="�����");
    bool contains(Point2f pt);
    bool contains(Point pt);

    //����
	friend ostream &operator<<(ostream &os, const Polygon &p);


};

//util
double calAngleInDegree(Point2f left, Point2f center, Point2f right);
double calCosine(double angleInDegree);
double angleInDegree2Arc(double angleInDegree);
double angleInArc2Degree(double angleInArc);

#endif // SHAPE_H
