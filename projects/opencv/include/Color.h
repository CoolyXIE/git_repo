#ifndef COLOR_H
#define COLOR_H
#include <core/core.hpp>
#include <highgui/highgui.hpp>

using namespace cv;

//��������
const int HSV_H_MAX = 180;  //ʵ��Ϊ360��
const int HSV_H_MIN = 0;
const int HSV_S_MAX = 255;
const int HSV_S_MIN = 0;
const int HSV_V_MAX = 255;
const int HSV_V_MIN = 0;

const int WHITE_S_MAX = 30;
const int WHITE_V_MIN = 221;
const int BLACK_V_MAX = 46;
const int BLACK_V_MIN = 0;
const int GRAY_S_MAX = 43;
const int GRAY_S_MIN = 0;
const int GRAY_V_MAX = 220;
const int GRAY_V_MIN = 46;

//�ж�������ɫ
bool isWhite(Vec3b hsv);
bool isBlack(Vec3b hsv);
bool isGray(Vec3b hsv);

//��������Ὣimg����color��ɫ�ݼ�ת��Ϊ�Ҷ�ͼ��Խ�ӽ�color,�Ҷ�ֵԽ��
Mat grayingColor(Mat &img, int color);

#endif // COLOR_H
