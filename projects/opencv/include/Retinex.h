#ifndef RETINEX_H
#define RETINEX_H

#include <string>
#include <core/core.hpp>
using namespace std;
using namespace cv;
class Retinex
{
    public:
        Retinex();
        virtual ~Retinex();
        void loadImg(string filePath);
        Mat &getImg();
        Mat SSR(int ksize = 3);
    protected:

    private:
        Mat img;
};

#endif // RETINEX_H


void testSSRRetinex(string filePath);
