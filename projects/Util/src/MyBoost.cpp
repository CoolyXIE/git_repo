#include "MyBoost.h"

MyBoost::MyBoost(){
    //ctor
}

MyBoost::~MyBoost(){
    //dtor
}


void MyBoost::split(string line, vector<string>& result, string delim){
    boost::split(result, line, is_any_of(delim));
}
