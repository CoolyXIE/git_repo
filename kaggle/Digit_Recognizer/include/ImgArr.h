#ifndef IMGARR_H
#define IMGARR_H

#include "cv.h"
using namespace std;

class ImgArr
{
    public:
        ImgArr();
        virtual ~ImgArr();

        void preProcess(IplImage* srcImg);

        const double getDist(ImgArr* img1, ImgArr* img2);


        int imgVal[28][28];
        int label;
};

#endif // IMGARR_H
