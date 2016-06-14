#ifndef CLASSIFER_H
#define CLASSIFER_H

#include <string>

class Classifer
{
    public:
        Classifer();
        virtual ~Classifer();

        int recognize(std::string img_path);

    protected:

    private:
};

#endif // CLASSIFER_H
