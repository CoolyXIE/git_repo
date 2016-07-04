#include "Feature.h"
#include "Basic.h"
#include <core/core.hpp>
#include <xfeatures2d.hpp>
#include <highgui/highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

Feature::Feature() {
    //ctor
}

Feature::Feature(int algorithm){
    this->algorithm = algorithm;
}

Feature::~Feature() {
    //dtor
}

void Feature::loadImg(string imgPath) {
    this->img = imread(imgPath);
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


//∆•≈‰
vector<DMatch> Feature::BFmatch(Feature &img) {
    vector<DMatch> matches;
    cv::BFMatcher matcher(cv::NORM_L2);
    matcher.match(this->descriptors, img.getDescriptors(), matches);
    return matches;
}

vector<DMatch> BFmatch(Feature &img1, Feature &img2){
    vector<DMatch> matches;
    BFMatcher matcher(NORM_L2);
    matcher.match(img1.getDescriptors(), img2.getDescriptors(), matches);
    return matches;
}


//ª≠Õº∫Ø ˝
Mat Feature::drawKeyPoints(){
    Mat out;
    cv::drawKeypoints(this->img, this->keypoints, out);
    showImg(out, "Ãÿ’˜µ„");
}

Mat Feature::drawMatches(Feature &img, vector<DMatch> &matches){
    Mat out;
    cv::drawMatches(this->img, this->getKeyPoints(), img.getSrcImg(), img.getKeyPoints(), matches, out);
    showImg(out, "∆•≈‰Õº∆¨");
    return out;
}


//≤‚ ‘∫Ø ˝




