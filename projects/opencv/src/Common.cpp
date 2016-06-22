#include "Common.h"

using namespace std;
using namespace cv;

void showImg(Mat img, string title){
    namedWindow(title.c_str());
    imshow(title.c_str(), img);
}

vector<int> getPixel(Mat &img, int x, int y){
    vector<int> result;
    if(img.channels() == 1){
        int val = img.at<uchar>(x, y);
        result.push_back(val);
    } else if(img.channels() == 3){
        int B = img.at<Vec3b>(x,y)[0];
        int G = img.at<Vec3b>(x,y)[1];
        int R = img.at<Vec3b>(x,y)[2];
        result.push_back(B);
        result.push_back(G);
        result.push_back(R);
    }
    return result;
}

