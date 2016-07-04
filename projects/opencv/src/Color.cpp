#include "Color.h"
#include "Basic.h"
#include <math.h>
#include <imgproc/imgproc.hpp>

using namespace cv;

Mat grayingColor(Mat &img, int color){
    const int GRAY_MAX = 255;
    Mat grayImg = Mat(img.size(), CV_8UC1);
    Mat hsvImg = Mat(img.size(), CV_8UC3);
    cvtColor(img, hsvImg, CV_BGR2HSV);
    for(int i = 0; i < hsvImg.size[0]; i ++){
        for(int j = 0; j < hsvImg.size[1]; j ++){
            Vec3b hsv = hsvImg.at<Vec3b>(i,j);
            if(isBlack(hsv) || isWhite(hsv) || isGray(hsv))
                grayImg.at<uchar>(i,j) = 0;
            else{
                int h = hsv[0];
                double dist = Min(abs(h - color), HSV_H_MAX - abs(h - color));
                int grayValue = 255 - (int)dist / (0.5 * HSV_H_MAX) * GRAY_MAX;
                grayImg.at<uchar>(i,j) = grayValue;
            }
        }
    }
    return grayImg;
}

bool isWhite(Vec3b hsv) {
    if (hsv[2] >= WHITE_V_MIN && hsv[1] <= WHITE_S_MAX)
        return true;
    else
        return false;
}

bool isBlack(Vec3b hsv) {
    if (hsv[2] <= BLACK_V_MAX)
        return true;
    else
        return false;
}

bool isGray(Vec3b hsv) {
    if (hsv[1] <= GRAY_S_MAX && hsv[2] >= GRAY_V_MIN && hsv[2] <= GRAY_V_MAX)
        return true;
    else
        return false;
}


