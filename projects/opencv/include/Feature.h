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

    //����ͼƬ
    void loadImg(string imgPath);
    void loadImg(Mat img);

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
    Mat drawMatches(Feature &img, vector<DMatch> &matches);

    //ƥ��
    vector<DMatch> BFmatch(Feature &img);

};

#endif // FEATURE_H

vector<DMatch> BFmatch(Feature &img1, Feature &img2);
Mat drawMatches(Feature &img1, Feature &img2, vector<DMatch> &matches);

