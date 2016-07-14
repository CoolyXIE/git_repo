#include "MyBoost.h"

void MyBoost::split(string line, vector<string>& result, string delim){
    boost::split(result, line, is_any_of(delim));
}
