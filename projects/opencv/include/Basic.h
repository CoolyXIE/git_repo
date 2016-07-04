#ifndef HELPER_H
#define HELPER_H
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <string>
#include <vector>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace cv;

//定义的常量


//常用内联函数
int Max(int a, int b);
int Min(int a, int b);

// ===============**Image显示保存**==========================

//将图像img显示在窗口title中
void showImg(Mat img, string title="图像");

//将图像img保存为filePath
void saveImg(Mat img, string filePath);

// =================**Video操作**================================

void playVideo(vector<Mat> &imgVec, double fps);

void saveVideo(vector<Mat> &imgVec, double fps, string videoPath);

// ====================**像素操作**======================
/*  得到一个图像像素点(x,y)的值
    如果img是灰度，则返回的vector只有一个值
    如果img是彩色的，则返回的vector有三个值，B-G-R的顺序
*/
vector<int> getPixel(Mat &img, int x, int y);

//图像转像素，将像素按从左到右，从上到下的顺序全部放入vector中，返回Size
Size convert2D(Mat &img, vector<int> &pixels);
Size convert3D(Mat &img, vector<Vec3b> &pixels);

//像素转图像，顺序同上
Mat convert2D(vector<int> &pixels, Size size);
Mat convert3D(vector<Vec3b> &pixels, Size size);

//得到领域点，按左上到右下的顺序，只返回位置，不考虑范围
vector<Point> getSurround4Points(Point center);
vector<Point> getSurround8Points(Point center);

/*====================**二值图像**=============================s
*/
//把二值图像与动态二值串的互相转换
void mat2DyBitset(Mat &img, boost::dynamic_bitset<> &bset);
void dyBitset2Mat(boost::dynamic_bitset<> &bset, Mat &img);

//把二值串按照图像规格保存下来，使用notepad++打开非常清楚
void saveBistSet(boost::dynamic_bitset<> &bset, int cols, string filePath);

#endif // HELPER_H
