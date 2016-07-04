#ifndef REGION_H
#define REGION_H
#include <core.hpp>
#include <boost/dynamic_bitset.hpp>

using namespace cv;

//��������
const int FLOOD_FILL_THRESHOLD = (int)(10 / 360.0 * 180.0);


/*
 ===============**��ˮ���**===================
ϣ������һ��ͼ�񣬸���һ����seed���ҳ���HSV�ռ�����seed��ɫ������ͬ����ͨ����
ȱ�㣺����������ʱ�䳤���ų���ɫ����ɫ�ͺ�ɫ
��Ҫ�Լ�������ֵ������seed��ɫ������ͬ����ͨ����
1.Ҫ��ʹ�ð�ɫ����ɫ�ͺ�ɫ����Ҫʹ��HSV��S��V����
2.����ͨ������㷨̫����
 */
Mat floodfill(Mat img, Point seed, int threshold = FLOOD_FILL_THRESHOLD);

boost::dynamic_bitset<> erodeBitset(boost::dynamic_bitset<> &before, Size size, int range = 1);

Mat getConnectRegion(Mat binImg, Point seed);
#endif // REGION_H
