#pragma once
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include "Matcher.h"

#ifndef SHAPETRANSFER_H
#define SHAPETRANSFER_H
using namespace std;
using namespace cv;
enum{CIRCLE, RECTANGLE, TRIANGLE};

class ShapeTransfer{
public:
	ShapeTransfer(){};
	ShapeTransfer(Mat &modelImg, Mat &testImg, Rect &rect);
	~ShapeTransfer(){};

	//homography
	void calAllHomography();

    //core
    Mat transferAndDetect(int shapeType);

	//each step
    void step1_imgTransfer();
    vector<vector<Point2f>> step2_detectShapeContours(int shapeType);
    Mat step3_drawOnQuery(vector<vector<Point2f>> shapeContours);

private:
	Mat trainImg;
	Mat queryImg;
	Mat rectImg;
	Rect rect;
	Mat imgToDetect;

    bool homographyIsEmpty;

	vector<Point2f> queryRectPoints;

	Mat homographyT2Q;
	Mat homographyQ2T;

};

void testShapeTransfer(int shapeType);
#endif // SHAPETRANSFER_H

