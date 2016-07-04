#pragma once
#ifndef SHAPEDETECTOR_H
#define SHAPEDETECTOR_H

#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;
void testMain();
class Line {
public:
	Point beginPoint;
	Point endPoint;

	Line(Point beginPoint, Point endPoint);
};

class Circle {
public:
	Point2f center;
	float radius;

	Circle(Point2f center, float radius);
	friend ostream &operator<<(ostream &os, const Circle &c);
};

class Rectangle {
public:
	//成员变量
	vector<Point> points;

	//构造析构函数
	Rectangle(vector<Point> &points);

	friend ostream &operator<<(ostream &os, const Rectangle &r);
};

class Polygon {
public:
	//成员变量
	int sides;
	vector<Point> points;

	//构造析构函数
	Polygon();
	Polygon(vector<Point> &points);

	//自定义函数
	vector<Point> &getAllPoints();
	vector<double> getAllEdgesLen();
	double getLeastEdgeLen();

	//重载输出
	friend ostream &operator<<(ostream &os, const Polygon &p);
};

class ShapeDetector {
private:
	Mat img;
public:
	//constructor
	ShapeDetector();
	ShapeDetector(Mat &img);
	virtual ~ShapeDetector();

	//detect
	vector<Line> detectLinesByHough();
	vector<Circle> detectCirclesByHough(double threRatio = 0.05);
	vector<Rectangle> detectRectanglesByContour(double biasAngle = 8); //检测矩形，允许直角有偏差，只有当四个角都在(90 - biasAngle, 90 + biasAngle)的范围内才判定为矩形
	vector<Polygon> detectPolygonsByContour(int edges);
	//检测指定边数的多边形

	//    vector<Polygon> detectRegularPolygonsByContour(int edges, double biasAngle = 8); //检测正多边形
    //optimize 优化程序
    /*  opt1_mergeSimilarPoint()函数解释：
    由于两个顶点离得很近导致本应是三角形的多边形被检测为四边形，本函数将合并两个距离很近的点
    srcPolygon: 要优化的原始多边形
    expectEdges: 期望合并相近顶点后的多边形边数
    threRatio: 如果某一条边 < 第expectEdges大的边长 * threRatio，那么则合并该边的两个顶点*/
	Polygon opt1_mergeSimilarPoint(Polygon srcPolygon, int expectEdges, double threRatio = 0.1);

	/*  opt2_mergeSimilarPoint()函数解释：
	检测出两个多边形几乎重合，本函数会将多个两两相近的多边形合并为一个多边形
	srcPolygons: 要优化的原始多边形的vector
	edges: 多边形边数
	threRatio: 当两个多边形相互比较时，每对相近的点之间的距离 < 两个多边形的最短边长 * threRatio，则合并这两个多边形
	*/
	vector<Polygon> opt2_mergeSimilarPolygons(vector<Polygon> srcPolygons, int edges, double threRatio = 0.5);

	vector<Circle> opt3_mergeSimilarCircles(vector<Circle> srcCircles, double threRatio = 0.05);

	//util
	/*  判断两个多边形是否相近，如果每对相近的点的距离都 < 两个多边形的最短边长 * threRatio，则认为这两个多边形相近 */
	bool isSimilar(Polygon &polygon1, Polygon &polygon2, double threRatio = 0.1);
	bool isSimilar(Circle &circle1, Circle &circle2, double threRatio = 0.05);
	/*  按照model多边形的顺序，矫正另一个与model几乎重合的顶点的顺序， 使两个多边形点集中两个相似的顶点的下标对应*/
	void correctSimilarVertexOrder(Polygon &model, Polygon &target);
	double angle(Point pt1, Point pt0, Point pt2);


	//draw 在成员变量img上画图
	Mat drawCircles(vector<Circle> &circles, Scalar color = Scalar(255,0,0), int thickness = 2);
	Mat drawPolygons(vector<Polygon> &polygons, Scalar color = Scalar(255, 0, 0), int thickness = 2);
	Mat drawRectangles(vector<Rectangle> &rectangles, Scalar color = Scalar(255, 0, 0), int thickness = 2);

	//get
	Mat &getModelImg();

};

#endif // SHAPEDETECTOR_H
