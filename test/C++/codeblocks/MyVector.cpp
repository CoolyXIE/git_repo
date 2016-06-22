#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct rect {
    int id;
    double length;
    double width;

    bool operator< (const rect &a ) const {
        return (length * width) < (a.length * a.width);
    }
} Rect;

void PrintVector(vector<Rect> &vec) {
    /*
        插一句，
        vec.begin()对应的位置是向量的第一个位置，
        vec.end()对应的是vector中的最后的一个元素位置的后面的一个位置（我认为，实际上是一个无效位置）
        文档上的定义：Returns an iterator referring to the past-the-end element in the vector container.
    */

    for(vector<Rect>::iterator it = vec.begin() ; it != vec.end() ; it++ ) {
        cout << it->id <<':'<< it->length << '*' << it->width << '=' << (it->length)*(it->width) << endl;
    }
}

void testSort(){

    vector<Rect> vec;
    Rect rect1 = {1, 2.0, 3.0};
    Rect rect2 = {2, 3.0, 5.0};
    Rect rect3 = {3, 1.0, 2.0};
    vec.push_back(rect1);
    vec.push_back(rect2);
    vec.push_back(rect3);
    cout << "before sort:\n" << endl;
    PrintVector(vec);
    sort(vec.begin(), vec.end());
    cout << "after sort:\n" << endl;
    PrintVector(vec);
}
int main() {
    vector<string> sentense;
    sentense.reserve(5); //预留5个元素空间，不够自动扩容
    sentense.push_back("Hello,");

    sentence.insert(sentense.end(), {"how", "are", "you", "?"});

    copy(sentence.cbegin(), sentence.cend(), ostream_iterator<string>(cout, " "));
    return 0;
}

