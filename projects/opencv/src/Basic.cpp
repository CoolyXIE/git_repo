#include "Basic.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <imgproc/imgproc.hpp>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace cv;

int Max(int a, int b) {
    if (a >= b)
        return a;
    else
        return b;
}

int Min(int a, int b) {
    if (a <= b)
        return a;
    else
        return b;
}

void showImg(Mat img, string title) {
    namedWindow(title.c_str(), WINDOW_NORMAL);
    imshow(title.c_str(), img);
}

void saveImg(Mat img, string filePath) {
    imwrite(filePath, img);
}

vector<int> getPixel(Mat &img, int row, int col) {
    vector<int> result;
    if(img.channels() == 1) {
        int val = img.at<uchar>(row, col);
        result.push_back(val);
    } else if(img.channels() == 3) {
        result.push_back(img.at<Vec3b>(row, col)[0]);
        result.push_back(img.at<Vec3b>(row, col)[1]);
        result.push_back(img.at<Vec3b>(row, col)[2]);
    }
    return result;
}

Size convert2D(Mat &grayImg, vector<int> &pixels) {
//  如果不是灰度图像，还要转为灰度图
    if (grayImg.channels() != 1)
        cvtColor(grayImg, grayImg, CV_BGR2GRAY);
    MatSize size = grayImg.size;
    //MatSize用下标获取行列数，Size用成员符号获取行列数
    int rows = size[0];  //行数
    int cols = size[1];  //列数
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            pixels.push_back(getPixel(grayImg, i, j)[0]);
        }
    }
    //Size(width, height)注意！
    return Size(cols, rows);
}

Size convert3D(Mat &colorImg, vector<Vec3b> &pixels) {
    MatSize size = colorImg.size;
    int rows = size[0];  //行数
    int cols = size[1];  //列数
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            vector<int> vec = getPixel(colorImg, i, j);
            Vec<uchar, 3> vec3b;
            vec3b[0] = vec[0];
            vec3b[1] = vec[1];
            vec3b[2] = vec[2];
            pixels.push_back(vec3b);
        }
    }
    return Size(cols, rows);
}

Mat convert2D(vector<int> &pixels, Size size) {
    int rows = size.height;
    int cols = size.width;
    Mat img = Mat(rows, cols, CV_8UC1);
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            img.at<uchar>(i,j) = (uchar)pixels[i*cols+j];
        }
    }
    return img;
}

Mat convert3D(vector<Vec3b> &pixels, Size size) {
    int rows = size.height;
    int cols = size.width;
    Mat img = Mat(rows, cols, CV_8UC3);
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            img.at<Vec3b>(i,j) = pixels[i*cols+j];
        }
    }
    return img;
}

vector<Point> getSurround4Points(Point center) {
    int row = center.x;
    int col = center.y;
    vector<Point> points;
    points.push_back(Point(row - 1, col));      //上
    points.push_back(Point(row, col - 1));      //左
    points.push_back(Point(row, col + 1));      //右
    points.push_back(Point(row + 1, col));      //下
    return points;
}

vector<Point> getSurround8Points(Point center) {
    int row = center.x;
    int col = center.y;
    vector<Point> points;
    points.push_back(Point(row - 1, col - 1));  //左上
    points.push_back(Point(row - 1, col));      //上
    points.push_back(Point(row - 1, col + 1));  //右上
    points.push_back(Point(row, col - 1));      //左
    points.push_back(Point(row, col + 1));      //右
    points.push_back(Point(row + 1, col - 1));  //左下
    points.push_back(Point(row + 1, col));      //下
    points.push_back(Point(row + 1, col + 1));  //右下
    return points;
}

void dyBitset2Mat(boost::dynamic_bitset<> &bset, Mat &img) {
    int rows = img.size[0];
    int cols = img.size[1];
    vector<int> v;
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            v.push_back(bset[i*cols+j] * 255);
        }
    }
    img = convert2D(v, Size(cols, rows));
}

void mat2DyBitset(Mat &img, boost::dynamic_bitset<> &bset) {
    int rows = img.size[0];
    int cols = img.size[1];
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {

            if(getPixel(img, i, j)[0] == 255) {
                bset[i*cols+j] = 1;
            }
        }

    }
}

void saveBistSet(boost::dynamic_bitset<> &bset, int cols, string filePath) {
    int rows = bset.size() / cols;
    int remain = bset.size() % cols;

    ofstream ofile(filePath);
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            ofile << bset[i*cols+j];
        }
        ofile << endl;
    }
    for(int i = 0; i < remain; i ++){
        ofile << bset[rows*cols+i];
    }
    ofile << endl;
    ofile.close();
}








