#include <opencv.hpp>
#include<core/core.hpp>
#include<highgui/highgui.hpp>
#include<imgproc/imgproc.hpp>
#include "xfeatures2d.hpp"
#include "ShapeDetector.h"
#include "ShapeTransfer.h"
#include "Matcher.h"
#include "Basic.h"
#include "Shape.h"
#include <math.h>
#include <set>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

ShapeTransfer::ShapeTransfer(Mat &modelImg, Mat &testImg, Rect &rect){
    cout << "初始化...";
    this->trainImg = modelImg;
    this->queryImg = testImg;
    this->rect = rect;
    this->rectImg = trainImg(rect);
    calAllHomography();
}

void ShapeTransfer::calAllHomography(){
    getHomography(this->rectImg, this->queryImg, this->rect, this->homographyT2Q, this->homographyQ2T);
    if(!this->homographyT2Q.empty()){
        this->homographyIsEmpty = false;
    } else{
        this->homographyIsEmpty = true;
    }
}

void ShapeTransfer::step1_imgTransfer(){
    Polygon polygon = Polygon(queryRectPoints);
	Mat queryRectImg = polygon.getIncludeImg(this->queryImg);
    warpPerspective(queryRectImg, this->imgToDetect, this->homographyQ2T, queryRectImg.size());
}

vector<vector<Point2f>> ShapeTransfer::step2_detectShapeContours(int shapeType){
    vector<vector<Point2f>> shapeContours;
    ShapeDetector detector = ShapeDetector(this->imgToDetect);
    if(shapeType == CIRCLE){
        vector<Circle> circles = detector.detectCirclesByHough();
        for(int i = 0; i < circles.size(); i ++)
            shapeContours.push_back(Point_toPoint2f(circles[i].getContourPoints()));
    } else if (shapeType == RECTANGLE){
        vector<Rectangle> rectangles = detector.detectRectanglesByContour();
        for(int i = 0; i < rectangles.size(); i ++){
            vector<Point2f> newBoxPoints;
            perspectiveTransform(this->queryRectPoints, newBoxPoints, this->homographyQ2T);
            Polygon boxPolygon(newBoxPoints);
            Polygon rectPolygon(rectangles[i].points);
            ShapeDetector s;
            s.setEdgeDistRatio2(0.03);
            if(!s.isSimilar(boxPolygon, rectPolygon))
                shapeContours.push_back(rectangles[i].points);
        }
    } else if (shapeType == TRIANGLE){
        vector<Polygon> triangles = detector.detectPolygonsByContour(3);
        for(int i = 0; i < triangles.size(); i ++)
            shapeContours.push_back(triangles[i].points);
    } else
        cout << "暂不提供此形状的检测" << endl;
    return shapeContours;
}

Mat ShapeTransfer::step3_drawOnQuery(vector<vector<Point2f>>shapeContours){
    vector<vector<Point>> shapeContoursOnQuery;
    for(int i = 0; i < shapeContours.size(); i ++){
        vector<Point2f> contourPoints;
        perspectiveTransform(shapeContours[i], contourPoints, this->homographyT2Q);
        shapeContoursOnQuery.push_back(Point2f_toPoint(contourPoints));
    }
    Mat outImg;
    drawContours(outImg, shapeContoursOnQuery, -1, Scalar(0, 0, 255), 2);
    return outImg;
}

Mat ShapeTransfer::transferAndDetect(int shapeType){
    if(this->homographyIsEmpty){
        cout << "empty, 结束" << endl;
        return this->queryImg;
    }
    step1_imgTransfer();
    return step3_drawOnQuery(step2_detectShapeContours(shapeType));
    cout << "识别, 结束" << endl;
}

void test1(){
//    Mat trainImg = imread("train2.jpg");
//    Mat queryImg = imread("query2.jpg");
////    Rect rect = Rect(477, 303, 180, 180); //1
//    Rect rect = Rect(171, 804, (683-171), (1276-804)); //2
//    Point2f leftUp(242, 880);
//    Point2f rightDown(547, 1189);
//    Ellipse ellipse(leftUp, rightDown);
//
//    Mat H1;
//    Mat H2;
//    getHomography(trainImg, queryImg, H1, H2, ellipse);
//    double time = getTickCount();
//    ShapeTransfer s = ShapeTransfer(trainImg, queryImg, rect);
//    s.setHomographyT2Q(H1);
//    s.setHomographyQ2T(H2);
//    time = (getTickCount() - time) / getTickFrequency();
//    cout << "第〇步花费时间:" << time << endl;
//    s.transferAndDetect(CIRCLE);
//    waitKey(0);
}


