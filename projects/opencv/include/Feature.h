#ifndef FEATURE_H
#define FEATURE_H

#include <features2d/features2d.hpp>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;

enum{SURF, SIFT,};

class Feature{
private:
    int algorithm;
    Mat img;
    vector<KeyPoint> keypoints;
    Mat descriptors;

public:
    Feature(int algorithm = 0);
    ~Feature();

    //����ͼƬ
    void loadImg(string imgPath);
    void loadImg(Mat &img);

    //����������
    void detectAndCompute();
    void detect();
    void compute();

    //get����
    Mat &getSrcImg();
    vector<KeyPoint> &getKeyPoints();
    Mat &getDescriptors();

    //��ͼ����
    Mat drawKeyPoints();
};

#endif // FEATURE_H

