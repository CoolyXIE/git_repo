#pragma once
#ifndef SHAPEDETECTOR_H
#define SHAPEDETECTOR_H

#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "Shape.h"
#include <vector>

using namespace std;
using namespace cv;

class ShapeDetector {
private:
	Mat img;
    double angleBias;
    double pointDistRatio1;
    double edgeDistRatio2;
    double leastShapeArea;
    Rect insideRect;
    Rect outsideRect;

public:
	//constructor
	ShapeDetector(){};
	virtual ~ShapeDetector(){};
    ShapeDetector(Mat &img);

    //set parameter
    void setAngleBias(double biasInDegree);
    void setPointDistRatio1(double pointDistRatio1);
    void setEdgeDistRatio2(double edgeDistRatio2);
    void setLeastShapeArea(double leastArea);
    void setInsideRect(Rect insideRect);
    void setOutsideRect(Rect outsideRect);

	//detect
    vector<Circle> detectCirclesByContour(); //to-do
	vector<Line> detectLinesByHough();
	vector<Circle>detectCirclesByHough();
	vector<Rectangle> detectRectanglesByContour();
	vector<Polygon> detectPolygonsByContour(int edges);

//  vector<Polygon> detectRegularPolygonsByContour(int edges, double biasAngle = 8); //to-do


	//optimize
	Polygon opt1_mergeSimilarPoint(Polygon srcPolygon, int expectEdges);
	vector<Polygon> opt2_mergeSimilarPolygons(vector<Polygon> srcPolygons);
	vector<Circle> opt3_mergeSimilarCircles(vector<Circle> srcCircles);
    void opt4_filterSmallAngle(vector<Polygon> &srcPolygons);
    void opt5_filterConcavePolygons(vector<Polygon> &srcPolygons);

	//util
	bool isSimilar(Polygon &polygon1, Polygon &polygon2);
	bool isSimilar(Circle &circle1, Circle &circle2);
    void correctSimilarVertexOrder(Polygon &model, Polygon &target);
    void limitContoursInsideRect(vector<vector<Point>> &contours);
    void limitContoursOutsideRect(vector<vector<Point>> &contours);


	//draw 在成员变量img上画图
	Mat drawCircles(vector<Circle> &circles, Scalar color = Scalar(255,0,0), int thickness = 2);
	Mat drawPolygons(vector<Polygon> &polygons, Scalar color = Scalar(255, 0, 0), int thickness = 2);
	Mat drawRectangles(vector<Rectangle> &rectangles, Scalar color = Scalar(255, 0, 0), int thickness = 2);
};

//实时检测
void detectRectangleRealTime();
void detectQuadrangleRealTime();


#endif // SHAPEDETECTOR_H
