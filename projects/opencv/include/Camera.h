#ifndef CAMERA_H
#define CAMERA_H

#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;


class Camera{
    public:
        Camera();  //��ʼ������ͷ
        virtual ~Camera();

        //get member
        double getFps();

        //
        Mat getFrame();
        void getFrameVec(vector<Mat> &imgVec, int max, double f);
    protected:

    private:
        VideoCapture capture;
        double fps;
};

#endif // CAMERA_H

/*
1. ��ȡ��ǰһ֡ͼ��
2. ��ָ��֡�ʻ�ȡһϵ����Ƭ
3.

*/
