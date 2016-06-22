#ifndef CLASSIFER_H
#define CLASSIFER_H
#include "ImgArr.h"
#include <string>

class Classifer
{
    public:
        Classifer();
        virtual ~Classifer();

        int recognize(ImgArr imgArr, const int k);

        vector<ImgArr> loadTrainFile();

    protected:

    private:
};

#endif // CLASSIFER_H
