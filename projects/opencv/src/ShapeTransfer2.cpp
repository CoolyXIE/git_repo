#include "ShapeDetector.h"
#include "ShapeTransfer2.h"
#include "ShapeTransfer.h"
#include "Basic.h"
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "xfeatures2d.hpp"
#include <math.h>
#include <set>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

//构造函数
ShapeTransfer2::ShapeTransfer2()
{


}


ShapeTransfer2::ShapeTransfer2(Mat &modelImg, Mat &testImg, Rect &rect)
{
    this->m_trainImg = modelImg;
    this->m_queryImg = testImg;
    this->m_rect = rect;
}



ShapeTransfer2::~ShapeTransfer2()
{


}



//计算单应矩阵


void ShapeTransfer2::setHomographyFromTrainToQuery(Mat &homographyT2Q)
{
	this->m_matHomographyT2Q = homographyT2Q;
}

void ShapeTransfer2::setHomographyFromQueryToTrain(Mat &homographyQ2T)
{
	this->m_matHomographyQ2T = homographyQ2T;
}


//Step-1
vector<Point2f> ShapeTransfer2::step1_boxTransfer()
{
	vector<Point2f> vecPointsCorners, vecPointsCornersTrans;
	vecPointsCorners.push_back(Point2f(this->m_rect.x, this->m_rect.y));
	vecPointsCorners.push_back(Point2f(this->m_rect.x + this->m_rect.width, this->m_rect.y));
	vecPointsCorners.push_back(Point2f(this->m_rect.x + this->m_rect.width, this->m_rect.y + this->m_rect.height));
	vecPointsCorners.push_back(Point2f(this->m_rect.x, this->m_rect.y + this->m_rect.height));
	perspectiveTransform(vecPointsCorners, vecPointsCornersTrans, this->m_matHomographyT2Q);

	this->m_matSmallHomographyT2Q = findHomography(Mat(vecPointsCorners), Mat(vecPointsCornersTrans), CV_LMEDS);
	this->m_matSmallHomographyQ2T = findHomography(Mat(vecPointsCornersTrans), Mat(vecPointsCorners), CV_LMEDS);
	perspectiveTransform(vecPointsCornersTrans, this->m_TrainViewPoint2fOfRect, this->m_matSmallHomographyQ2T);
	return vecPointsCornersTrans;
}

//Step-2
Mat ShapeTransfer2::step2_getImageOfTest(vector<Point2f> &quadranglePoints)
{
	Polygon polygon = Polygon(quadranglePoints);
	Mat res;
	res=polygon.getIncludeImg(this->m_queryImg);
	return res;
}



//Step-3

Mat ShapeTransfer2::step3_revertImage(Mat Image)
{
	Mat resImage;
	warpPerspective(Image, resImage, this->m_matSmallHomographyQ2T, Size(Image.cols, Image.rows));
	return resImage;
}


//Step-4: 检测变换好的图像中的指定形状
vector<vector<Point2f>> ShapeTransfer2::step4_detectShapeContoursUnderTrainView(int shapeType, Mat &revertedBoxImg)
{

    vector<vector<Point2f>> shapeContours;
    ShapeDetector detector = ShapeDetector(revertedBoxImg);
    if(shapeType == CIRCLE){
        vector<Circle> circles = detector.detectCirclesByHough();
        for(int i = 0; i < circles.size(); i ++)
            shapeContours.push_back(Point_toPoint2f(circles[i].getContourPoints()));
    } else if (shapeType == RECTANGLE){
        vector<Rectangle> rectangles = detector.detectRectanglesByContour();
        for(int i = 0; i < rectangles.size(); i ++)
            shapeContours.push_back(rectangles[i].points);
    } else if (shapeType == TRIANGLE){
        vector<Polygon> triangles = detector.detectPolygonsByContour(3);
        for(int i = 0; i < triangles.size(); i ++)
            shapeContours.push_back(triangles[i].points);
    } else
        cout << "暂不提供此形状的检测" << endl;


	if (shapeType == RECTANGLE)
	{
		float maxArea = 0, tempArea;
		int indexOfMaxArea;
		for (int k = 0; k < shapeContours.size(); k++)
		{
			tempArea = contourArea(shapeContours[k], false);
			if (tempArea > maxArea)
			{
				maxArea = tempArea;
				indexOfMaxArea = k;
			}
		}

		Polygon polygonFromTrainViewPoint = Polygon(this->m_TrainViewPoint2fOfRect);
		Polygon polygonTemp = Polygon(shapeContours[indexOfMaxArea]);
		vector < vector<Point2f>>shapeContoursRemained;
		ShapeDetector s;
		s.setEdgeDistRatio2(0.1);
		if (s.isSimilar(polygonFromTrainViewPoint, polygonTemp))
		{

			for (int i = 0; i < shapeContours.size(); i++)
			{
				if (i != indexOfMaxArea)
					shapeContoursRemained.push_back(shapeContours[i]);
			}
		}

		shapeContours = shapeContoursRemained;

	}

    return shapeContours;
}

//Step-5: 把检测出来的轮廓点变换到Test图像上的形状轮廓
vector<vector<Point2f>> ShapeTransfer2::step5_convertShapeContoursOnQuery(vector<vector<Point2f>> &detectedContours)
{
	vector<vector<Point2f>> resultContours;
    for(int i = 0; i < detectedContours.size(); i ++)
	{
        vector<Point2f> points_trans;
		perspectiveTransform(detectedContours[i], points_trans, this->m_matSmallHomographyT2Q);

       resultContours.push_back(points_trans);
    }
	return resultContours;
}

void ShapeTransfer2::step6_draw(vector<vector<Point2f>> contours){
    vector<vector<Point>> p;
    for(int i = 0; i < contours.size(); i ++)
        p.push_back(Point2f_toPoint(contours[i]));
    drawContours(this->m_queryImg, p, -1, Scalar(0,0,255));
}


void ShapeTransfer2::detectShapeContoursOnQueryImg(int shapeType)
{
	vector<Point2f> quadranglePoints = step1_boxTransfer();
	Mat resulImage =step2_getImageOfTest(quadranglePoints);
	Mat revertedBoxImg = step3_revertImage(resulImage);
	vector<vector<Point2f>> detectedContours = step4_detectShapeContoursUnderTrainView(shapeType, revertedBoxImg);
	step6_draw(step5_convertShapeContoursOnQuery(detectedContours));
}

int main(){
    Mat query = imread("query1.jpg");
    Mat train = imread("train1.jpg");
    Mat H_Q2T = getHomography(query, train);
    Mat H_T2Q = getHomography(train, query);
    Rect rect = Rect(477, 303, 180, 180);


    ShapeTransfer2 s = ShapeTransfer2(train, query, rect);
    s.setHomographyFromQueryToTrain(H_Q2T);
    s.setHomographyFromTrainToQuery(H_T2Q);
    s.detectShapeContoursOnQueryImg(0);
    showImg(query);
    waitKey(0);


    return 0;
}
