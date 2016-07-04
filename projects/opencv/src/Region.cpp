#include "Region.h"
#include "Basic.h"
#include "Color.h"
#include <boost/dynamic_bitset.hpp>
#include <core/core.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

boost::dynamic_bitset<> erodeBitset(boost::dynamic_bitset<> &before, Size size, int range) {
    int len = before.size();
    boost::dynamic_bitset<> after(len);
    int rows = size.height;
    int cols = size.width;
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            if(before[i*cols+j] == 1) {
                //在range范围的正方体都set为1
                for(int k = -range; k <= range; k ++) {
                    for(int l = -range; l <= range; l ++) {
                        int row = i + k;
                        int col = j + l;
                        if(row >= 0 && row < rows && col >= 0 && col < cols)
                            after[row * cols + col] = 1;
                    }
                }
            }
        }
    }
    return after;
}

Mat floodfill(Mat img, Point seed, int threshold) {
    int rows = img.size[0];
    int cols = img.size[1];

//    转化为HSV图像
    Mat img_HSV;
    cvtColor(img, img_HSV, CV_BGR2HSV);

//    根据阈值确定颜色范围
    int seedColor = getPixel(img_HSV, seed.x, seed.y)[0];
    int max = seedColor + threshold;
    int min = seedColor - threshold;

//    判断
    bool isContinuous;
    if (max > HSV_H_MAX) {
        max = max - HSV_H_MAX;
        isContinuous = false;
    } else if (min < 0) {
        min = min + HSV_H_MAX;
        isContinuous = false;
    } else
        isContinuous = true;

    cout << "种子点：(" << seed.x+1 << ", " << seed.y+1 << ") , " << "种子颜色：" << seedColor << endl;
    cout << "H值范围：" << min << " ~ " << max << endl;


//    使用白色作为背景
    const Vec3b BG_COLOR_HSV= {0, 0, 255};
    Mat result = Mat(rows, cols, CV_8UC3);
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            result.at<Vec3b>(i,j) = BG_COLOR_HSV;
        }
    }

//    提取种子点相同颜色的连通区域，算法时间太久
    vector<Point> bound;
    vector<Point> resultSet;

    bound.push_back(seed);
    resultSet.push_back(seed);
    while(!bound.empty()) {
        Point boundPoint = bound.front();
        bound.erase(bound.begin());
        cout << "点(" << boundPoint.x+1 << ", " << boundPoint.y+1 << ")已取出并移除" << endl;
//        把周围8个新出现的像素推到边界并保存到set
        vector<Point> points = getSurround8Points(boundPoint); //默认八连通
        for(int i = 0; i < points.size(); i ++) {
            Point p = points[i];
            if(p.x >= 0 && p.y >= 0 && p.x < rows && p.y < cols) {
                Vec3b hsv = img_HSV.at<Vec3b>(p.x, p.y);
                cout << "\t周围点：" << p.x+1 << ", " << p.y+1;
                cout << ", H值：" << (int)hsv[0] <<" ,";
                int color = hsv[0];
                if(find(resultSet.begin(), resultSet.end(), p) == resultSet.end()) {
                    cout << "在set中找不到, ";
                    if(!isWhite(hsv) && !isBlack(hsv) && !isGray(hsv)) {
                        cout << "不是白色、黑色或灰色, ";
                        if ((isContinuous && (color <= max && color >= min)) || (!isContinuous && (color <= max || color >= min))) {
                            bound.push_back(p);
                            resultSet.push_back(p);
                            cout << "added!";
                        }
                    }
                }
            }
            cout << "size: " << bound.size() << endl;
            getchar();
        }
    }

//    完成连通分量的提取后，将resultSet的点恢复原图像的颜色
    for(int i = 0; i < resultSet.size(); i ++) {
        int row = resultSet[i].x;
        int col = resultSet[i].y;
        result.at<Vec3b>(row,col) = img_HSV.at<Vec3b>(row,col);
    }
    cvtColor(result, result, CV_HSV2BGR); //转化回BGR图像
    return result;
}

Mat getConnectRegion(Mat srcBImg, Point seed) {
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
    //如果没有二值化，要先二值化
    int rows = srcBImg.size[0];
    int cols = srcBImg.size[1];
    Size size = Size(cols, rows);
    int len = rows * cols;


//    将图形转为bitset
    boost::dynamic_bitset<> srcBSet(len);
    mat2DyBitset(srcBImg, srcBSet);
//    printRange(srcBSet, cols, seed, 1);

    //开始循环，先初始化seed点
    boost::dynamic_bitset<> beforeBSet(len);
    boost::dynamic_bitset<> middleBSet(len);
    boost::dynamic_bitset<> afterBSet(len);

    Mat beforeBImg = Mat(rows, cols, CV_8U);
    Mat middleBImg = Mat(rows, cols, CV_8U);
    Mat afterBImg = Mat(rows, cols, CV_8U);


    int seedIndex = seed.x * cols + seed.y;
    beforeBSet[seedIndex] = 1;
    //将before转化为Mat做膨胀
    dyBitset2Mat(beforeBSet, beforeBImg);
    dilate(beforeBImg, middleBImg, Mat());
//        showImg(middleBImg);
    mat2DyBitset(middleBImg, middleBSet);

    //将middle转化回BitSet与源图像的Bitset求交集
    afterBSet = middleBSet & srcBSet;
    dyBitset2Mat(afterBSet, afterBImg);
//    showImg(afterBImg);
//    waitKey(0);
//    停止条件是before和after相同

    while(afterBSet != beforeBSet) {
        beforeBSet = afterBSet;
        dyBitset2Mat(beforeBSet, beforeBImg);
        dilate(beforeBImg, middleBImg, element);
//             showImg(middleBImg);
        mat2DyBitset(middleBImg, middleBSet);

        afterBSet = middleBSet & srcBSet;
        dyBitset2Mat(afterBSet, afterBImg);
//        showImg(afterBImg);
//        waitKey(0);
    }

    //转换为图像返回
    return afterBImg;
}
