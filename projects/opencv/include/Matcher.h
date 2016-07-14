#ifndef MATCHER_H
#define MATCHER_H
#include "Feature.h"
#include <xfeatures2d.hpp>
#include <vector>

using namespace std;

class Matcher{
enum{BF, KNN, FLANN, };
public:
    virtual ~Matcher(){};
    Matcher(Feature &query, Feature &train, int matchMethod = 0);

    //set method
    void setMatchMethod(int matchMethod);

    //match
    void match();
    void knnMatch(int k = 2);

    //filter
    void keepGoodMatches(int times = 2);
    void filterMatches();

    //draw
    Mat drawMatches();
    Mat drawGoodMatches();
    Mat drawFilteredMatches();

    //homography
    Mat getHomographyAfterFilter();

    //get
    vector<DMatch> &getFilteredMatches();
    vector<DMatch> &getMatches();
    vector<DMatch> &getGoodMatches();
    vector<KeyPoint> &getQueryKeyPoints();
    vector<KeyPoint> &getTrainKeyPoints();


private:
    int matchMethod;
    Feature query;
    Feature train;

    vector<vector<DMatch>> knnMatches;
    vector<vector<DMatch>> knnMatchesReversed;
    vector<DMatch> matches;
    vector<DMatch> goodMatches;
    vector<DMatch> filteredMatches;
    vector<Point> filteredQueryPoints;
    vector<Point> filteredTrainPoints;
};


Mat getHomography(Mat &trainImg, Mat &queryImg);
Mat getHomography(Mat& trainImg, Mat& queryImg, Rect rect);
void getHomography(Mat &train, Mat &query, Rect rect, Mat &H_T2Q, Mat &H_Q2T);
void getHomography(Mat &train, Mat &query, Ellipse &ellipse, Mat &H_T2Q, Mat &H_Q2T);

void filter1_ratioTest(vector<vector<DMatch>> &matches, float r=0.6f);
void filter2_symmetry(vector<vector<DMatch>> &matches1, vector<vector<DMatch>>&matches2, vector<DMatch>&symMatches);
void filter3_RANSAC(vector<DMatch> &matches, vector<KeyPoint> vecQueryKeyPoint2f, vector<KeyPoint> vecTrainKeyPoint2f);
#endif // MATCHER_H
