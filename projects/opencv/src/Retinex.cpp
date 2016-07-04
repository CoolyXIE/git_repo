#include "Retinex.h"
#include "Basic.h"
#include <math.h>
#include <iostream>
#include <imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Retinex::Retinex()
{
    //ctor
}

Retinex::~Retinex()
{
    //dtor
}


Mat &Retinex::getImg(){
    return this->img;
}

void Retinex::loadImg(string filePath){
    Mat grayImg;
    cvtColor(imread(filePath), grayImg, CV_BGR2GRAY);
    this->img = grayImg;
}

Mat Retinex::SSR(int ksize){
    Mat lightness;
    Mat logLightness = Mat(lightness.size(), CV_8UC1);
    Mat logSrcImg = Mat(this->img.size(), CV_8UC1);
    Mat resultImg = Mat(this->img.size(), CV_8UC1);
    GaussianBlur(this->img, lightness, Size(ksize, ksize),0);
    int Max = 0;
    int Min = 10000;

    for(int i = 0; i < this->img.rows; i ++){
        for(int j = 0; j < this->img.cols; j ++){

            logLightness.at<uchar>(i,j) = (uchar)std::log(getPixel(this->img, i,j)[0]+1.0);
            logSrcImg.at<uchar>(i,j) = (uchar)std::log(getPixel(this->img, i,j)[0] + 1.0);
       cout << "here" << endl;
            resultImg.at<uchar>(i,j) = logSrcImg.at<uchar>(i,j) - logLightness.at<uchar>(i,j);
            if(resultImg.at<uchar>(i,j) > Max)
                Max = resultImg.at<uchar>(i,j);
            if(resultImg.at<uchar>(i,j) <Max)
                Min = resultImg.at<uchar>(i,j);
        }
    }

    for(int i = 0; i < this->img.rows; i ++){
        for(int j = 0; j < this->img.cols; j ++){
                resultImg.at<uchar>(i,j) = (resultImg.at<uchar>(i,j) - Min) / (Max - Min) * (255 - 0);
        }
    }

    return resultImg;
}

void testSSRRetinex(string filePath){
    Retinex r;
    r.loadImg(filePath);
    showImg(r.getImg(), "Ô´Í¼Ïñ");
    showImg(r.SSR(), "SSR");
    waitKey(0);
}
void testSSRRetinex();
