#include "Feature.h"
#include "Basic.h"
#include <core/core.hpp>
#include <opencv.hpp>
#include <xfeatures2d.hpp>
#include <highgui/highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

Feature::Feature(int algorithm) {
    this->algorithm = algorithm;
}

Feature::~Feature() {
    //dtor
}

void Feature::loadImg(string imgPath) {
    this->img = imread(imgPath);
}

void Feature::loadImg(Mat &img) {
    this->img = img;
}

void Feature::detect() {
    if(algorithm == SIFT) {
        cv::Ptr<cv::Feature2D> siftPtr = cv::xfeatures2d::SIFT::create();
        siftPtr->detect(this->img, this->keypoints);
    } else if(algorithm == SURF) {
        cv::Ptr<cv::Feature2D> surfPtr = cv::xfeatures2d::SURF::create();
        surfPtr->detect(this->img, this->keypoints);
    }
}

void Feature::compute() {
    if(this->getKeyPoints().size() == 0)
        return ;

    if(algorithm == SIFT) {
        cv::Ptr<cv::Feature2D> siftPtr = cv::xfeatures2d::SIFT::create();
        siftPtr->compute(this->img, this->keypoints, this->descriptors);
    } else if (algorithm == SURF) {
        cv::Ptr<cv::Feature2D> surfPtr = cv::xfeatures2d::SURF::create();
        surfPtr->compute(this->img, this->keypoints, this->descriptors);
    }

}

void Feature::detectAndCompute() {
    detect();
    compute();
}

Mat &Feature::getSrcImg() {
    return this->img;
}

vector<KeyPoint> &Feature::getKeyPoints() {
    return this->keypoints;
}

Mat &Feature::getDescriptors() {
    return this->descriptors;
}

//»­Í¼º¯Êý
Mat Feature::drawKeyPoints() {
    Mat out;
    cv::drawKeypoints(this->img, this->keypoints, out);
    showImg(out, "ÌØÕ÷µã");
    return out;
}


