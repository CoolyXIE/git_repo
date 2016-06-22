#ifndef CAMERA_H
#define CAMERA_H

#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;


class Camera{
    public:
        Camera();  //初始化摄像头
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
1. 获取当前一帧图像
2. 按指定帧率获取一系列照片
3.

*/
