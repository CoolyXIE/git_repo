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
	//��Ա����
	vector<Point> points;

	//������������
	Rectangle(vector<Point> &points);

	friend ostream &operator<<(ostream &os, const Rectangle &r);
};

class Polygon {
public:
	//��Ա����
	int sides;
	vector<Point> points;

	//������������
	Polygon();
	Polygon(vector<Point> &points);

	//�Զ��庯��
	vector<Point> &getAllPoints();
	vector<double> getAllEdgesLen();
	double getLeastEdgeLen();

	//�������
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
	vector<Rectangle> detectRectanglesByContour(double biasAngle = 8); //�����Σ�����ֱ����ƫ�ֻ�е��ĸ��Ƕ���(90 - biasAngle, 90 + biasAngle)�ķ�Χ�ڲ��ж�Ϊ����
	vector<Polygon> detectPolygonsByContour(int edges);
	//���ָ�������Ķ����

	//    vector<Polygon> detectRegularPolygonsByContour(int edges, double biasAngle = 8); //����������
    //optimize �Ż�����
    /*  opt1_mergeSimilarPoint()�������ͣ�
    ��������������úܽ����±�Ӧ�������εĶ���α����Ϊ�ı��Σ����������ϲ���������ܽ��ĵ�
    srcPolygon: Ҫ�Ż���ԭʼ�����
    expectEdges: �����ϲ���������Ķ���α���
    threRatio: ���ĳһ���� < ��expectEdges��ı߳� * threRatio����ô��ϲ��ñߵ���������*/
	Polygon opt1_mergeSimilarPoint(Polygon srcPolygon, int expectEdges, double threRatio = 0.1);

	/*  opt2_mergeSimilarPoint()�������ͣ�
	������������μ����غϣ��������Ὣ�����������Ķ���κϲ�Ϊһ�������
	srcPolygons: Ҫ�Ż���ԭʼ����ε�vector
	edges: ����α���
	threRatio: ������������໥�Ƚ�ʱ��ÿ������ĵ�֮��ľ��� < ��������ε���̱߳� * threRatio����ϲ������������
	*/
	vector<Polygon> opt2_mergeSimilarPolygons(vector<Polygon> srcPolygons, int edges, double threRatio = 0.5);

	vector<Circle> opt3_mergeSimilarCircles(vector<Circle> srcCircles, double threRatio = 0.05);

	//util
	/*  �ж�����������Ƿ���������ÿ������ĵ�ľ��붼 < ��������ε���̱߳� * threRatio������Ϊ�������������� */
	bool isSimilar(Polygon &polygon1, Polygon &polygon2, double threRatio = 0.1);
	bool isSimilar(Circle &circle1, Circle &circle2, double threRatio = 0.05);
	/*  ����model����ε�˳�򣬽�����һ����model�����غϵĶ����˳�� ʹ��������ε㼯���������ƵĶ�����±��Ӧ*/
	void correctSimilarVertexOrder(Polygon &model, Polygon &target);
	double angle(Point pt1, Point pt0, Point pt2);


	//draw �ڳ�Ա����img�ϻ�ͼ
	Mat drawCircles(vector<Circle> &circles, Scalar color = Scalar(255,0,0), int thickness = 2);
	Mat drawPolygons(vector<Polygon> &polygons, Scalar color = Scalar(255, 0, 0), int thickness = 2);
	Mat drawRectangles(vector<Rectangle> &rectangles, Scalar color = Scalar(255, 0, 0), int thickness = 2);

	//get
	Mat &getModelImg();

};

#endif // SHAPEDETECTOR_H
