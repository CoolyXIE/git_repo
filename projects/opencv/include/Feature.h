#ifndef FEATURE_H
#define FEATURE_H

#include <features2d/features2d.hpp>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;

enum{SIFT, SURF};

class Feature{
private:
    int algorithm;
    Mat img;
    vector<KeyPoint> keypoints;
    Mat descriptors;

public:
    Feature();
    Feature(int algorithm);
    ~Feature();

    //载入图片
    void loadImg(string imgPath);
    void loadImg(Mat img);

    //计算特征点
    void detectAndCompute();
    void detect();
    void compute();

    //get函数
    Mat &getSrcImg();
    vector<KeyPoint> &getKeyPoints();
    Mat &getDescriptors();

    //画图函数
    Mat drawKeyPoints();
    Mat drawMatches(Feature &img, vector<DMatch> &matches);

    //匹配
    vector<DMatch> BFmatch(Feature &img);

};

#endif // FEATURE_H

vector<DMatch> BFmatch(Feature &img1, Feature &img2);
Mat drawMatches(Feature &img1, Feature &img2, vector<DMatch> &matches);

