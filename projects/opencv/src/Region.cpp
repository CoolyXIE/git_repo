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
                //��range��Χ�������嶼setΪ1
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

//    ת��ΪHSVͼ��
    Mat img_HSV;
    cvtColor(img, img_HSV, CV_BGR2HSV);

//    ������ֵȷ����ɫ��Χ
    int seedColor = getPixel(img_HSV, seed.x, seed.y)[0];
    int max = seedColor + threshold;
    int min = seedColor - threshold;

//    �ж�
    bool isContinuous;
    if (max > HSV_H_MAX) {
        max = max - HSV_H_MAX;
        isContinuous = false;
    } else if (min < 0) {
        min = min + HSV_H_MAX;
        isContinuous = false;
    } else
        isContinuous = true;

    cout << "���ӵ㣺(" << seed.x+1 << ", " << seed.y+1 << ") , " << "������ɫ��" << seedColor << endl;
    cout << "Hֵ��Χ��" << min << " ~ " << max << endl;


//    ʹ�ð�ɫ��Ϊ����
    const Vec3b BG_COLOR_HSV= {0, 0, 255};
    Mat result = Mat(rows, cols, CV_8UC3);
    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            result.at<Vec3b>(i,j) = BG_COLOR_HSV;
        }
    }

//    ��ȡ���ӵ���ͬ��ɫ����ͨ�����㷨ʱ��̫��
    vector<Point> bound;
    vector<Point> resultSet;

    bound.push_back(seed);
    resultSet.push_back(seed);
    while(!bound.empty()) {
        Point boundPoint = bound.front();
        bound.erase(bound.begin());
        cout << "��(" << boundPoint.x+1 << ", " << boundPoint.y+1 << ")��ȡ�����Ƴ�" << endl;
//        ����Χ8���³��ֵ������Ƶ��߽粢���浽set
        vector<Point> points = getSurround8Points(boundPoint); //Ĭ�ϰ���ͨ
        for(int i = 0; i < points.size(); i ++) {
            Point p = points[i];
            if(p.x >= 0 && p.y >= 0 && p.x < rows && p.y < cols) {
                Vec3b hsv = img_HSV.at<Vec3b>(p.x, p.y);
                cout << "\t��Χ�㣺" << p.x+1 << ", " << p.y+1;
                cout << ", Hֵ��" << (int)hsv[0] <<" ,";
                int color = hsv[0];
                if(find(resultSet.begin(), resultSet.end(), p) == resultSet.end()) {
                    cout << "��set���Ҳ���, ";
                    if(!isWhite(hsv) && !isBlack(hsv) && !isGray(hsv)) {
                        cout << "���ǰ�ɫ����ɫ���ɫ, ";
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

//    �����ͨ��������ȡ�󣬽�resultSet�ĵ�ָ�ԭͼ�����ɫ
    for(int i = 0; i < resultSet.size(); i ++) {
        int row = resultSet[i].x;
        int col = resultSet[i].y;
        result.at<Vec3b>(row,col) = img_HSV.at<Vec3b>(row,col);
    }
    cvtColor(result, result, CV_HSV2BGR); //ת����BGRͼ��
    return result;
}

Mat getConnectRegion(Mat srcBImg, Point seed) {
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
    //���û�ж�ֵ����Ҫ�ȶ�ֵ��
    int rows = srcBImg.size[0];
    int cols = srcBImg.size[1];
    Size size = Size(cols, rows);
    int len = rows * cols;


//    ��ͼ��תΪbitset
    boost::dynamic_bitset<> srcBSet(len);
    mat2DyBitset(srcBImg, srcBSet);
//    printRange(srcBSet, cols, seed, 1);

    //��ʼѭ�����ȳ�ʼ��seed��
    boost::dynamic_bitset<> beforeBSet(len);
    boost::dynamic_bitset<> middleBSet(len);
    boost::dynamic_bitset<> afterBSet(len);

    Mat beforeBImg = Mat(rows, cols, CV_8U);
    Mat middleBImg = Mat(rows, cols, CV_8U);
    Mat afterBImg = Mat(rows, cols, CV_8U);


    int seedIndex = seed.x * cols + seed.y;
    beforeBSet[seedIndex] = 1;
    //��beforeת��ΪMat������
    dyBitset2Mat(beforeBSet, beforeBImg);
    dilate(beforeBImg, middleBImg, Mat());
//        showImg(middleBImg);
    mat2DyBitset(middleBImg, middleBSet);

    //��middleת����BitSet��Դͼ���Bitset�󽻼�
    afterBSet = middleBSet & srcBSet;
    dyBitset2Mat(afterBSet, afterBImg);
//    showImg(afterBImg);
//    waitKey(0);
//    ֹͣ������before��after��ͬ

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

    //ת��Ϊͼ�񷵻�
    return afterBImg;
}
