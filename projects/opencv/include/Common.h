#ifndef HELPER_H
#define HELPER_H
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;


//��ͼ��img��ʾ�ڴ���title��
void showImg(Mat img, string title);

//��ͼ��img����ΪfilePath
void saveImg(Mat img, string filePath);


// ======================**���ز���**======================
/*  �õ�һ��ͼ�����ص�(x,y)��ֵ
    ���img�ǻҶȣ��򷵻ص�vectorֻ��һ��ֵ
    ���img�ǲ�ɫ�ģ��򷵻ص�vector������ֵ��B-G-R��˳��
*/
vector<int> getPixel(Mat &img, int x, int y);

//  ͼ��ת���أ������ذ������ң����ϵ��µ�˳��ȫ������vector�У�����Size
Size convert2D(Mat &img, Vector<int> &pixels);
Size convert3D(Mat &img, Vector<Vec3b> &pixels);

//  ����תͼ��˳��ͬ��
Mat convert2D(Vector<int> &pixels, Size size);
Mat convert3D(Vector<Vec3b> &pixels, Size size);
// ============================================================


// ====================**����logo**============================
void mix(Mat &src, Mat &logo, Rect rect);

// ��ɫת������






//void playVideo(vector<Mat> &imgVec, double fps);

//void saveVideo(vector<Mat> &imgVec, double fps, string videoPath);




#endif // HELPER_H
