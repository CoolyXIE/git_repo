#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/dynamic_bitset.hpp>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include "Basic.h"
#include "Color.h"
#include "ShapeDetector.h"
#include "Region.h"
#include "Camera.h"
#include "Feature.h"
#include "Retinex.h"

using namespace cv;
using namespace std;


void testConvert() {
    /*测试2*/

    Mat img = imread("红色盖子.jpg");
    resize(img, img, Size(100, 80));
    vector<Vec3b> pixels;
    Size size = convert3D(img, pixels);

    for(int i = 0; i < size.height; i ++) {
        for(int j = 0; j < size.width; j ++) {
            Vec3b vec = pixels[i * size.width + j];
            for(int k = 0; k < 3; k ++)
                cout << (int)vec[k] << ",";
            cout << "\t";
        }
        cout << endl;
    }

    /*测试3*/

//    vector<int> pixels;
//    for(int i = 0; i < 256; i ++){
//        for(int j = 0; j < 256; j ++){
//            pixels.push_back(j);
//        }
//    }
//    Size size;
//    size.width = 256;
//    size.height = 256;
//    Mat img = convert2D(pixels, size);
//    showImg(img, "测试像素转灰度图");
//    waitKey(0);

    /*测试4*/

//    vector<Vec3b> pixels;
//    for(int i = 0; i < 256; i ++){
//        for(int j = 0; j < 256; j ++){
//            Vec3b BGR;
//            BGR[0] = (uchar)rand()%256;
//            BGR[1] = (uchar)rand()%256;
//            BGR[2] = (uchar)rand()%256;
//            pixels.push_back(BGR);
//        }
//    }
//    Size size;
//    size.width = 256;
//    size.height = 256;
//    Mat img = convert3D(pixels, size);
//    showImg(img, "测试像素转彩色图");
//    waitKey(0);

}

void testFloodFill() {
    Mat img = imread("红色盖子.jpg");
//    Point seed = Point(6,247); //上方蓝色
//    Point seed = Point(470, 237); //下方蓝色
//    Point seed = Point(369,57); //左下方红色盖子
//    Point seed = Point(159, 205);//中间红色盖子
    Point seed = Point(184,443); //右边红色盖子
    Mat img_result = floodfill(img, seed, 5);
    showImg(img_result);
    waitKey(0);
}

void hsv2csv() {
    Mat img = imread("红色盖子_small.jpg");
    ofstream out_H("红色盖子_H.csv");
    ofstream out_S("红色盖子_S.csv");
    ofstream out_V("红色盖子_V.csv");
    Mat img_HSV;
    cvtColor(img, img_HSV, CV_BGR2HSV);
    for(int i = 0; i < img_HSV.size[0]; i ++) {
        for(int j = 0; j < img_HSV.size[1]; j ++) {
            out_H << (int)img_HSV.at<Vec3b>(i,j)[0] << ",";
            out_S << (int)img_HSV.at<Vec3b>(i,j)[1] << ",";
            out_V << (int)img_HSV.at<Vec3b>(i,j)[2] << ",";
        }
        out_H << endl;
        out_S << endl;
        out_V << endl;
    }
    out_H.close();
    out_S.close();
    out_V.close();
}

void createPureWhiteImg() {
    Mat img = Mat(100, 1000, CV_8UC3);
    for(int i = 0; i < 100; i ++) {
        for(int j = 0; j < 1000; j ++) {
            img.at<Vec3b>(i,j) = {0, 0, 255};
        }
    }
    cvtColor(img, img, CV_HSV2BGR);
    showImg(img, "纯白");
    waitKey(0);
}

void testMatAt() {
//    Mat img = imread("test.jpg");
//    cvtColor(img, img, CV_BGR2GRAY);
//    resize(img, img, Size(3,2));
//    saveImg(img, "test_small.jpg");
//    cout << (int)img.at<uchar>(0,0) << "," << (int)img.at<uchar>(0,1) << "," << (int)img.at<uchar>(0,2) << endl;
//    cout << (int)img.at<uchar>(1,0) << "," << (int)img.at<uchar>(1,1) << "," << (int)img.at<uchar>(1,2) << endl;
//    cout << (int)img.at<uchar>(0,0) << "," << (int)img.at<uchar>(0,1) << endl;
//    cout << (int)img.at<uchar>(1,0) << "," << (int)img.at<uchar>(1,1) << endl;
//    cout << (int)img.at<uchar>(2,0) << "," << (int)img.at<uchar>(2,1) << endl;

}

void testErodeBitSet() {
    boost::dynamic_bitset<> b(16);
    b[5] = 1;
    Size size = Size(3,3);
    boost::dynamic_bitset<> after = erodeBitset(b, size);
    cout << after << endl;

}

void testDynamicBitSet() {
    boost::dynamic_bitset<> b(10);
    b[1] = 1;
    b[2] = 1;
    boost::dynamic_bitset<> s(10);
    s[3] = 1;
    s[2] = 1;
    cout << b << endl;
    cout << s << endl;
    boost::dynamic_bitset<> c = b & s;
    cout << c << endl;
}

void testGetConnectRegion() {
    Mat img = imread("test.jpg");
    Mat binImg = Mat(img.size[0], img.size[1], CV_8U);
    threshold(img, binImg, 150, 255, CV_THRESH_BINARY_INV);
    Point p = Point(374,720);
    Mat result = getConnectRegion(binImg, p);
    showImg(result);
    waitKey(0);
}

void resizeAndSave(string filePath) {
    Mat img = imread(filePath);
    resize(img, img, Size(img.size[0]/2, img.size[1]/2));
    threshold(img, img, 150, 255, CV_THRESH_BINARY);
    saveImg(img, filePath);
}

void binaryAndSave(string filePath){
    Mat img = imread(filePath);
    cvtColor(img, img, CV_BGR2GRAY);
    threshold(img, img, 128, 255, CV_THRESH_BINARY_INV);
    saveImg(img, filePath);
}

void getSizeContours(vector<vector<Point>> &contours){
    int cmin = 100;   // 最小轮廓长度
    int cmax = 1000;   // 最大轮廓长度
    vector<vector<Point>>::const_iterator itc = contours.begin();
    while(itc != contours.end())
    {
        if((itc->size()) < cmin || (itc->size()) > cmax)
        {
            itc = contours.erase(itc);
        }
        else ++ itc;
    }
}

void testContour(string filePath){
    Mat img = imread(filePath);
    Mat grayImg;
    cvtColor(img, grayImg, CV_BGR2GRAY);
        vector<vector<Point>> contours;
    findContours(grayImg, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    cout << contours.size() << endl;
    Mat show = Mat(grayImg.size(), CV_8U, Scalar(255));
    drawContours(show, contours, -1, Scalar(0), 1);
    showImg(show);
    waitKey(0);
}

void testColor(string filePath, Point seed){
    Mat img = imread(filePath);
    int red_H = 0;
    Mat gray = grayingColor(img, red_H);
    showImg(gray);
    waitKey(0);
    Mat binary;
    threshold(gray, binary, 230, 255, CV_THRESH_BINARY);
    //提取轮廓
    vector<vector<Point>> contours;
    findContours(binary, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    //提取凸包
    vector<vector<Point>> poly(contours.size());
    Mat result = Mat(img.size(), CV_8UC1);

    for(int i = 0; i < contours.size(); i ++){
//        cout << pointPolygonTest(contours[i], seed, 0) << endl;
        if(pointPolygonTest(contours[i], seed, 0) >= 0){
            drawContours(result, Mat(contours[i]), -1, Scalar(255), 1);
        }
    }
    //画图,结果有很多小的分量
    showImg(result);
    waitKey(0);
}

void testPointPolygonTest(string filePath, Point seed){
    Mat img = imread(filePath);
    cvtColor(img, img, CV_BGR2GRAY);
    threshold(img, img, 128, 255, CV_THRESH_BINARY);
    vector<vector<Point>> contours;
    findContours(img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    cout << contours.size() << endl;
    Mat result = Mat(img.size(), CV_8UC1);
    for(int i = 0; i < contours.size(); i ++){
        cout << pointPolygonTest(contours[i], seed, 0) << endl;
        drawContours(result, Mat(contours[i]), -1, Scalar(255), 1);
            showImg(result);
                waitKey(0);
    }


}

void testFeature(string filePath){
    Feature f = Feature(SIFT);
    f.loadImg(filePath);
    f.detectAndCompute();
    f.drawKeyPoints();
    waitKey(0);
}


int main(){
    testSSRRetinex("test.jpg");
    return 0;
}
