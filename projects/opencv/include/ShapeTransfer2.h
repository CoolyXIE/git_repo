#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

#ifndef SHAPETRANSFER_H
#define SHAPETRANSFER_H
using namespace std;
using namespace cv;

class ShapeTransfer2{
	enum{CIRCLE, RECTANGLE, TRIANGLE, };


public:
	ShapeTransfer2();
	ShapeTransfer2(Mat &modelImg, Mat &testImg, Rect &rect);
	~ShapeTransfer2();

    //match

	//homography
	void setHomographyFromTrainToQuery(Mat &homographyT2Q);
	void setHomographyFromQueryToTrain(Mat &homographyQ2T);

	//step
	vector<Point2f> step1_boxTransfer();
	Mat step2_getImageOfTest(vector<Point2f> &quadranglePoints);
	Mat step3_revertImage(Mat  roiImage);
	vector<vector<Point2f>> step4_detectShapeContoursUnderTrainView(int shapeType, Mat &revertedBoxImg);
	vector<vector<Point2f>> step5_convertShapeContoursOnQuery(vector<vector<Point2f>> &detectedContours);
    void step6_draw(vector<vector<Point2f>> contours);


	//core
	void detectShapeContoursOnQueryImg(int shapeType);

private:
	Mat m_trainImg;
	Mat m_queryImg;
	Rect m_rect;
	Mat m_matHomographyT2Q;
	Mat m_matHomographyQ2T;
	Mat m_matSmallHomographyT2Q;
	Mat m_matSmallHomographyQ2T;

	vector<Point2f> m_QueryPoint2f;
	vector<Point2f> m_TrainPoint2f;
	vector<Point2f> m_TrainViewPoint2fOfRect;
};
void test2();

#endif // SHAPETRANSFER_H

