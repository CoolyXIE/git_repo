#include<opencv2/core/core.hpp>
#include<Opencv2/core/cvstd.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

const int STANDARD_HEIGHT = 240;
const int STANDARD_WIDTH = 320;

Mat readImg(const string& imgPath)
{
	Mat srcImg = imread(imgPath);
	int width = srcImg.cols;
	int height = srcImg.rows;
	Mat stdImg;
	Mat grayImg;
	if (width < height)
		resize(srcImg, stdImg, Size(STANDARD_HEIGHT, STANDARD_WIDTH), 0, 0);
	else
		resize(srcImg, stdImg, Size(STANDARD_WIDTH, STANDARD_HEIGHT), 0, 0);
	cvtColor(stdImg, grayImg, CV_BGR2GRAY);
	return grayImg;
}

void test()
{
    Ptr<Feature2D> m_f2d = xfeatures2d::SURF::create();
    vector<KeyPoint> keyPoints;
    Mat model = readImg("test.jpg");
    m_f2d->detect(model, keyPoints);
    cout << keyPoints.size();
}

