#ifndef REGION_H
#define REGION_H
#include <core.hpp>
#include <boost/dynamic_bitset.hpp>

using namespace cv;

//常量定义
const int FLOOD_FILL_THRESHOLD = (int)(10 / 360.0 * 180.0);


/*
 ===============**漫水填充**===================
希望输入一幅图像，给定一个点seed，找出在HSV空间中与seed颜色近似相同的连通区域
缺点：不适用运算时间长，排除白色、灰色和黑色
需要自己设置阈值：定义seed颜色近似相同的连通区域
1.要想使用白色、灰色和黑色，需要使用HSV的S和V分量
2.找连通区域的算法太慢了
 */
Mat floodfill(Mat img, Point seed, int threshold = FLOOD_FILL_THRESHOLD);

boost::dynamic_bitset<> erodeBitset(boost::dynamic_bitset<> &before, Size size, int range = 1);

Mat getConnectRegion(Mat binImg, Point seed);
#endif // REGION_H
