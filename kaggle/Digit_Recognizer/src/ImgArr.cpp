#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "ImgArr.h"
#include "cv.h"
#include "highgui.h"

using namespace std;

ImgArr::ImgArr()
{
    //ctor
}


ImgArr::~ImgArr()
{
    //dtor
}

void ImgArr::preProcess(IplImage* srcImg){



    //灰度化处理
    IplImage* grayImg = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U, 1);
    cvCvtColor(srcImg,grayImg,CV_BGR2GRAY);

    //改变大小为28*28
    IplImage* smallImg = cvCreateImage(cvSize(28, 28), IPL_DEPTH_8U, 1);
    cvResize(grayImg, smallImg);

    //改为int[28][28]的成员类型
    int m = smallImg->height;
	int n = smallImg->width;
    uchar *ptr;

	for (int i=0; i<m; i++)
	{
		ptr = (uchar*)smallImg->imageData + i*smallImg->widthStep;
		for (int j=0; j<n; j++)
		{
			this->imgVal[i][j] = (int)*(ptr+j);
		}
	}

    //把这个矩阵写到txt文件
//    ofstream ofile("result.txt");
//    for (int i=0; i<m; i ++)
//    {
//        for (int j=0; j<n; j ++)
//        {
//            ofile << 255 - (this->imgVal[i][j]) << "\t";
//        }
//        ofile << "\n" << endl;
//    }
//    ofile.close();

    //输出小图片
//    cvNamedWindow( "small image", 0 );
//    cvShowImage("mall image", smallImg);




//    resize(grayImg,smallImg,Size(32,32),0,0,CV_INTER_LINEAR);
}

const double getDist(ImgArr* img1, ImgArr* img2)
{
    double dist = 0.0;
    for (int i=0; i < 28; i ++)
    {
        for (int j=0; j < 28; j ++)
        {
            dist += pow(((img1->imgVal[i][j]) - (img2->imgVal[i][j])), 2.0);
        }
    }
    return  pow(dist, 0.5);
}














