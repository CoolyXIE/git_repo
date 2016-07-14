#ifndef MYBOOST_H
#define MYBOOST_H
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>

using namespace boost;
using namespace std;

class MyBoost
{
    public:
        MyBoost(){};
        virtual ~MyBoost(){};

        //string
        static int string2int(string s);
        static double string2double(string s);
        static string double2string(double a);

        static void split(string line, vector<string>& result, string delim = "\t");
    private:
};

#endif // MYBOOST_H
