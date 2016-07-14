#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/dynamic_bitset.hpp>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include "Basic.h"
#include "Color.h"
#include "Shape.h"
#include "ShapeDetector.h"
#include "ShapeTransfer.h"
#include "Region.h"
#include "Camera.h"
#include "Feature.h"
#include "Retinex.h"
#include "../util/include/DirHelper.h"

using namespace cv;
using namespace std;

void modeling(string filePath) {
    Camera c;
    namedWindow("��Ƶ", WINDOW_NORMAL);
    cout << "���¿ո����ȡ��ģͼ��" << endl;
    Mat img;
    while(true) {
        img = c.getFrame();
        imshow("��Ƶ", img);
        int key = waitKey(1);
        if(key == 32) {
            cout << "��ý�ģͼ��"<< endl;
            break;
        } else if(key == 27) {
            cout << "�˳�" << endl;
            break;
        }
    }
    saveImg(img, filePath);
}

void testBox() {
    Mat modelImg = imread("E:\\model.jpg");
    Rect rect(201, 179, 243, 273);
    Rectangle(rect).drawOnImg(modelImg, "model");
    Camera c;
    Mat H;
    Mat queryImg;
    while(true) {
        queryImg = c.getFrame();
        H = getHomography(modelImg, queryImg, rect);
        if(!H.empty()) {
            vector<Point2f> quadrsOnQuery;
            perspectiveTransform(Rectangle(rect).points, quadrsOnQuery, H);
            Polygon quadr(quadrsOnQuery);
            quadr.drawOnImg(queryImg, "���");
        } else {
            showImg(queryImg, "���");
        }
        waitKey(100);
    }
}

//void testRect(){
//    DirHelper d("mobile");
//    vector<string> testFiles = d.getSpecFiles("jpg");
//    for(int i = 0; i < testFiles.size(); i ++){
//        cout << i << endl;
//        string filePath = testFiles[i];
//        Mat img = imread(filePath);
//        ShapeDetector s(img);
//        s.setAngleBias(10);
//        vector<Rectangle> rects = s.detectRectanglesByContour();
//        Mat result = s.drawRectangles(rects);
//        saveImg(result, "result_" + boost::lexical_cast<string>(i+1) + ".jpg");
//    }
//}

int fac(int n){
    return 3 * n;
}

void f1(const int &arg){

}

int main() {
    int n = 3;
    f1(3);
    return 0;
}


