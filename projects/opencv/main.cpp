#include <iostream>
#include <boost/lexical_cast.hpp>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include "Common.h"

using namespace std;
using namespace boost;
using namespace cv;

void testPixel(){
    Mat img = imread("test.jpg");

}


int main() {
    testPixel();
    return 0;
}
