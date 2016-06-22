#ifndef HELPER_H
#define HELPER_H
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;


//将图像img显示在窗口title中
void showImg(Mat img, string title);

//将图像img保存为filePath
void saveImg(Mat img, string filePath);


// ======================**像素操作**======================
/*  得到一个图像像素点(x,y)的值
    如果img是灰度，则返回的vector只有一个值
    如果img是彩色的，则返回的vector有三个值，B-G-R的顺序
*/
vector<int> getPixel(Mat &img, int x, int y);

//  图像转像素，将像素按从左到右，从上到下的顺序全部放入vector中，返回Size
Size convert2D(Mat &img, Vector<int> &pixels);
Size convert3D(Mat &img, Vector<Vec3b> &pixels);

//  像素转图像，顺序同上
Mat convert2D(Vector<int> &pixels, Size size);
Mat convert3D(Vector<Vec3b> &pixels, Size size);
// ============================================================


// ====================**叠加logo**============================
void mix(Mat &src, Mat &logo, Rect rect);

// 颜色转换函数






//void playVideo(vector<Mat> &imgVec, double fps);

//void saveVideo(vector<Mat> &imgVec, double fps, string videoPath);




#endif // HELPER_H
