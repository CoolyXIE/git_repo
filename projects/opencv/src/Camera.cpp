#include "Camera.h"
#include "Basic.h"
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace cv;


Camera::Camera(){
    this->capture.open(0);
    this->fps = capture.get(CV_CAP_PROP_FPS);
}

Camera::~Camera(){
    //dtor
}

Mat Camera::getFrame(){
    Mat frame;
    capture.read(frame);
    return frame;
}

void Camera::saveFrame(string filePath){
    Mat img = getFrame();
    saveImg(img, filePath);
}

double Camera::getFps(){
    return this->fps;
}

vector<Mat> Camera::getFramesBySpace(bool saveOnDisk, string dirPath){
    vector<Mat> resultImgs;
    namedWindow("��Ƶ", WINDOW_NORMAL);
    cout << "���¿ո����ȡͼ��" << endl;
    int index = 0;
    while(true){
        Mat img = getFrame();
        imshow("��Ƶ", img);
        int key = waitKey(1);
        if(key == 32){
            index++;
            cout << "��õ�" << index << "֡ͼ��"<< endl;
            resultImgs.push_back(img);
        }
        else if(key == 27){
            cout << "�˳�" << endl;
            break;
        }
    }
    if(saveOnDisk){
        for(int i = 0; i < resultImgs.size(); i ++){
            saveImg(resultImgs[i], dirPath + "\\" + boost::lexical_cast<string>(i+1) + ".jpg");
        }
    }
    return resultImgs;
}

void Camera::getFrameVec(vector<Mat> &imgVec, int max, double f){
    int delay = (int)1000/f;
    for(int i = 0; i < max; i ++){
        Mat img = getFrame();
        showImg(img, boost::lexical_cast<string>(i+1));
        imgVec.push_back(img);
        waitKey(delay);
    }
}



