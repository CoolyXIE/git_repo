#include "Camera.h"
#include "Basic.h"
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

double Camera::getFps(){
    return this->fps;
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




