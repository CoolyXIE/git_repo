#ifndef HELPER_H
#define HELPER_H
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <string>
#include <vector>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace cv;

//����ĳ���


//������������
int Max(int a, int b);
int Min(int a, int b);

// ===============**Image��ʾ����**==========================

//��ͼ��img��ʾ�ڴ���title��
void showImg(Mat img, string title="ͼ��");

//��ͼ��img����ΪfilePath
void saveImg(Mat img, string filePath);

// =================**Video����**================================

void playVideo(vector<Mat> &imgVec, double fps);

void saveVideo(vector<Mat> &imgVec, double fps, string videoPath);

// ====================**���ز���**======================
/*  �õ�һ��ͼ�����ص�(x,y)��ֵ
    ���img�ǻҶȣ��򷵻ص�vectorֻ��һ��ֵ
    ���img�ǲ�ɫ�ģ��򷵻ص�vector������ֵ��B-G-R��˳��
*/
vector<int> getPixel(Mat &img, int x, int y);

//ͼ��ת���أ������ذ������ң����ϵ��µ�˳��ȫ������vector�У�����Size
Size convert2D(Mat &img, vector<int> &pixels);
Size convert3D(Mat &img, vector<Vec3b> &pixels);

//����תͼ��˳��ͬ��
Mat convert2D(vector<int> &pixels, Size size);
Mat convert3D(vector<Vec3b> &pixels, Size size);

//�õ�����㣬�����ϵ����µ�˳��ֻ����λ�ã������Ƿ�Χ
vector<Point> getSurround4Points(Point center);
vector<Point> getSurround8Points(Point center);

/*====================**��ֵͼ��**=============================s
*/
//�Ѷ�ֵͼ���붯̬��ֵ���Ļ���ת��
void mat2DyBitset(Mat &img, boost::dynamic_bitset<> &bset);
void dyBitset2Mat(boost::dynamic_bitset<> &bset, Mat &img);

//�Ѷ�ֵ������ͼ���񱣴�������ʹ��notepad++�򿪷ǳ����
void saveBistSet(boost::dynamic_bitset<> &bset, int cols, string filePath);

#endif // HELPER_H
