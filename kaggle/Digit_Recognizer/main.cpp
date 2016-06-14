#include <iostream>
#include <string>
#include "Classifer.h"

using namespace std;

int main()
{
    string path;
    char img_path[100];
    int result_number = 0;
    Classifer classifer;
    cout << "Hello! This is a program for digit recognize." << endl;
    cin.getline(img_path, 100);
    path = img_path;
    cout << path << endl;
    result_number = classifer.recognize(path);
    cout <<"this may be number: " << result_number << endl;
    return 0;
}
