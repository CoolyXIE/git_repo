#include "Shape.h"
#include "Feature.h"
#include "Matcher.h"
#include <core/core.hpp>
#include <opencv.hpp>
#include <xfeatures2d.hpp>
#include "Basic.h"
#include <vector>

using namespace std;
using namespace cv;

Matcher::Matcher(Feature &query, Feature &train, int matchMethod) {
    this->query = query;
    this->train = train;
    this->matchMethod = matchMethod;
}

void Matcher::setMatchMethod(int matchMethod) {
    this->matchMethod = matchMethod;
}

void Matcher::match() {
    if(this->query.getDescriptors().empty())
        return;

    if(this->matchMethod == BF) {
        BFMatcher matcher(cv::NORM_L2);
        matcher.match(this->query.getDescriptors(), this->train.getDescriptors(), this->matches);
    } else if(this->matchMethod == FLANN) {
        FlannBasedMatcher matcher;
        matcher.match(this->query.getDescriptors(), this->train.getDescriptors(), this->matches);
    } else
        cout << "match method wrong!" << endl;
}

void Matcher::knnMatch(int k) {
    if(this->matchMethod == BF) {
        BFMatcher matcher(cv::NORM_L2);
        matcher.knnMatch(this->query.getDescriptors(), this->train.getDescriptors(), this->knnMatches, k);
        matcher.knnMatch(this->train.getDescriptors(), this->query.getDescriptors(), this->knnMatchesReversed, k);
    } else if(this->matchMethod == FLANN) {
        FlannBasedMatcher matcher;
        matcher.knnMatch(this->query.getDescriptors(), this->train.getDescriptors(), this->knnMatches, k);
        matcher.knnMatch(this->train.getDescriptors(),this->query.getDescriptors(),  this->knnMatchesReversed, k);
    } else
        cout << "match method wrong!" << endl;
}

void Matcher::keepGoodMatches(int n) {
    double max_dist = 0;
    double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for(int i = 0; i < this->matches.size(); i++) {
        double dist = this->matches[i].distance;
        if(dist < min_dist)
            min_dist = dist;
        if(dist > max_dist)
            max_dist = dist;
    }

    //-- Draw only "good" matches (i.e. whose distance is less than n * min_dist )
    vector<DMatch> good_matches;
    for(int i = 0; i < this->matches.size(); i++ ) {
        if(this->matches[i].distance < n * min_dist) {
            good_matches.push_back(this->matches[i]);
        }
    }
    this->goodMatches = good_matches;
}

void Matcher::filterMatches() {
    knnMatch(2);
    vector<vector<DMatch>> knnmatches1 = this->knnMatches;
    vector<vector<DMatch>> knnmatches2 = this->knnMatchesReversed;

    filter1_ratioTest(knnmatches1);
    filter1_ratioTest(knnmatches2);

    filter2_symmetry(knnmatches1, knnmatches2, this->filteredMatches);

//    filter3_RANSAC(this->filteredMatches, this->query.getKeyPoints(), this->train.getKeyPoints());

    vector<Point> filteredQueryPoints, filteredTrainPoints;
    for (vector<DMatch>::const_iterator it = filteredMatches.begin(); it != filteredMatches.end(); ++it) {
        filteredQueryPoints.push_back(this->query.getKeyPoints()[it->queryIdx].pt);
        filteredTrainPoints.push_back(this->train.getKeyPoints()[it->trainIdx].pt);
    }
    this->filteredQueryPoints = filteredQueryPoints;
    this->filteredTrainPoints = filteredTrainPoints;
}

Mat Matcher::drawMatches() {
    vector<KeyPoint> queryKeyPoints = this->query.getKeyPoints();
    vector<KeyPoint> trainKeyPoints = this->train.getKeyPoints();

    for (int i = 0; i < this->matches.size(); i++) {
        queryKeyPoints.push_back(queryKeyPoints[this->matches[i].queryIdx]);
        trainKeyPoints.push_back(queryKeyPoints[this->matches[i].trainIdx]);
    }
    Mat result;
    cv::drawMatches(this->query.getSrcImg(), queryKeyPoints, this->train.getSrcImg(), trainKeyPoints, this->matches, result, DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    showImg(result, "matches");
    return result;
}

Mat Matcher::drawGoodMatches() {
    vector<KeyPoint> queryKeyPoints = this->query.getKeyPoints();
    vector<KeyPoint> trainKeyPoints = this->train.getKeyPoints();

    for (int i = 0; i < this->goodMatches.size(); i++) {
        queryKeyPoints.push_back(queryKeyPoints[this->matches[i].queryIdx]);
        trainKeyPoints.push_back(queryKeyPoints[this->matches[i].trainIdx]);
    }
    Mat result;
    cv::drawMatches(this->query.getSrcImg(), queryKeyPoints, this->train.getSrcImg(), trainKeyPoints, this->goodMatches, result, DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    showImg(result, "good matches");
    return result;
}

Mat Matcher::drawFilteredMatches() {
    vector<KeyPoint> queryKeyPoints = this->query.getKeyPoints();
    vector<KeyPoint> trainKeyPoints = this->train.getKeyPoints();

    for (int i = 0; i < this->filteredMatches.size(); i++) {
        queryKeyPoints.push_back(queryKeyPoints[this->filteredMatches[i].queryIdx]);
        trainKeyPoints.push_back(queryKeyPoints[this->filteredMatches[i].trainIdx]);
    }
    Mat result;
    cv::drawMatches(this->query.getSrcImg(), queryKeyPoints, this->train.getSrcImg(), trainKeyPoints, this->filteredMatches, result, DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    showImg(result, "filtered matches");
    return result;


}

Mat Matcher::getHomographyAfterFilter() {
    //make sure you have already calculated  filtered matches
    vector<Point2f> queryPoints;
    vector<Point2f> trainPoints;
    for (int i = 0; i < this->filteredMatches.size(); i++) {
        queryPoints.push_back(this->query.getKeyPoints()[filteredMatches[i].queryIdx].pt);
        trainPoints.push_back(this->train.getKeyPoints()[filteredMatches[i].trainIdx].pt);
    }
    Mat H = findHomography(queryPoints, trainPoints, CV_RANSAC);
    return H;
}

vector<DMatch> &Matcher::getMatches(){
    return this->matches;
}

vector<DMatch> &Matcher::getGoodMatches(){
    return this->goodMatches;
}
vector<KeyPoint> &Matcher::getQueryKeyPoints(){
    return this->query.getKeyPoints();
}
vector<KeyPoint> &Matcher::getTrainKeyPoints(){
    return this->train.getKeyPoints();
}

vector<DMatch> &Matcher::getFilteredMatches(){
    return this->filteredMatches;
}

void filter1_ratioTest(vector<vector<DMatch>> &matches, float r) {
    for (vector<vector<DMatch>>::iterator matchIterator = matches.begin(); matchIterator != matches.end(); ++matchIterator) {
        if (matchIterator->size() > 1) {
            if ((*matchIterator)[0].distance / (*matchIterator)[1].distance > r) {
                matchIterator->clear();
            }
        } else {
            matchIterator->clear();
        }
    }
}

void filter2_symmetry(vector<vector<DMatch>>&matches1, vector<vector<DMatch>>&matches2, vector<DMatch>&symMatches) {
    //遍历图1到图2的所有匹配
    for (vector<vector<DMatch>>::iterator matchIterator1 = matches1.begin(); matchIterator1 != matches1.end(); ++matchIterator1) {
        if (matchIterator1->size() < 2)
            continue;
        //遍历图2到图1的所有匹配
        for (vector<vector<DMatch>>::iterator matchIterator2 = matches2.begin(); matchIterator2 != matches2.end(); ++matchIterator2) {
            if (matchIterator2->size() < 2)
                continue;
            if ((*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx && (*matchIterator2)[0].queryIdx == (*matchIterator1)[0].trainIdx) {
                symMatches.push_back(DMatch((*matchIterator1)[0].queryIdx, (*matchIterator1)[0].trainIdx, (*matchIterator1)[0].distance));
                break;
            }
        }

    }
}

void  filter3_RANSAC(vector<DMatch> &matches, vector<KeyPoint> vecQueryKeyPoint2f, vector<KeyPoint> vecTrainKeyPoint2f) {

    //Mat  Homography;
    vector<Point2f> vecQueryPoint2f, vecTrainPoint2f;
    for (vector<DMatch>::const_iterator it = matches.begin(); it != matches.end(); ++it) {
        vecQueryPoint2f.push_back(vecQueryKeyPoint2f[it->queryIdx].pt);
        vecTrainPoint2f.push_back(vecTrainKeyPoint2f[it->trainIdx].pt);
    }

    vector<uchar> inliers(vecQueryPoint2f.size(), 0);
    Mat fundemental = findFundamentalMat(Mat(vecQueryPoint2f), Mat(vecTrainPoint2f), inliers, CV_FM_RANSAC);


    vector<uchar>::const_iterator itIn = inliers.begin();
    vector<DMatch>::const_iterator itM = matches.begin();

    vector<DMatch>outMatches;
    for (; itIn != inliers.end(); ++itIn, ++itM) {

        if (*itIn) {
            outMatches.push_back(*itM);
        }
    }

    bool refineF = true;// false
    vector<DMatch>midOutMatches = outMatches;
    if (refineF) {
        vecQueryPoint2f.clear();
        vecTrainPoint2f.clear();

        for (vector<DMatch>::const_iterator it1 = outMatches.begin(); it1 != outMatches.end(); ++it1) {
            vecQueryPoint2f.push_back(vecQueryKeyPoint2f[it1->queryIdx].pt);
            vecTrainPoint2f.push_back(vecTrainKeyPoint2f[it1->trainIdx].pt);
        }
        vector<uchar> newinliers(vecQueryPoint2f.size(), 0);

        fundemental = findFundamentalMat(Mat(vecQueryPoint2f), Mat(vecTrainPoint2f), newinliers, CV_FM_RANSAC);
        //Homography = findHomography(Mat(Point2f2fs1), Mat(Point2f2fs2), CV_LMEDS);
        itIn = newinliers.begin();
        itM = midOutMatches.begin();

        outMatches.clear();
        for (; itIn != newinliers.end(); ++itIn, ++itM) {

            if (*itIn) {
                outMatches.push_back(*itM);
            }
        }

    }
    matches = outMatches;
}


void getHomography(Mat &trainImg, Mat &queryImg, Ellipse &ellipse, Mat &H_T2Q, Mat &H_Q2T) {
//    Feature train = Feature();
//    train.loadImg(trainImg);
//    train.detectAndCompute();
//
//    Feature query = Feature();
//    query.loadImg(queryImg);
//    query.detectAndCompute();
//
//    Matcher m = Matcher(query, train);
//    m.match();
//    m.keepGoodMatches();
//    m.filterMatches();
//
//    vector<DMatch> matches = m.getFilteredMatches();
//
//    vector<Point2f> queryPoints;
//    vector<Point2f> trainPoints;
//
//    vector<DMatch> finalMatches;
//    for (int i = 0; i < matches.size(); i++) {
//        Point2f trainPt = train.getKeyPoints()[matches[i].trainIdx].pt;
//        if(ellipse.contains(trainPt)) {
//            queryPoints.push_back(query.getKeyPoints()[matches[i].queryIdx].pt);
//            trainPoints.push_back(trainPt);
//        }
//    }
//    H1 = findHomography(trainPoints, queryPoints, CV_RANSAC);
//    H2 = findHomography(queryPoints, trainPoints, CV_RANSAC);
}

void getHomography(Mat& trainImg, Mat& queryImg, Rect rect, Mat &H_T2Q, Mat &H_Q2T) {
    Feature train = Feature();
    train.loadImg(trainImg);
    train.detectAndCompute();

    Feature query = Feature();
    query.loadImg(queryImg);
    query.detectAndCompute();

    Matcher m = Matcher(train, query);



    m.match();
    m.keepGoodMatches();
    m.filterMatches();

    vector<DMatch> matches = m.getFilteredMatches();

    vector<Point2f> queryPoints;
    vector<Point2f> trainPoints;

    vector<DMatch> finalMatches;
    for (int i = 0; i < matches.size(); i++) {
        Point2f trainPt = train.getKeyPoints()[matches[i].trainIdx].pt;
        if(rect.contains(Point((int)trainPt.x, (int)trainPt.y))) {
            queryPoints.push_back(query.getKeyPoints()[matches[i].queryIdx].pt);
            trainPoints.push_back(trainPt);
            finalMatches.push_back(matches[i]);
        }
    }
    if(trainPoints.size() >=4 && (queryPoints.size() == trainPoints.size())) {
        H_T2Q = findHomography(trainPoints, queryPoints);

        vector<Point2f> points;
        perspectiveTransform(Rectangle(rect).points, points, H_T2Q);
        Polygon polygon(points);

        vector<Point2f> queryPts, trainPts;
        for (int i = 0; i < queryPoints.size(); i ++) {
            if (polygon.contains(queryPoints[i])){
                queryPts.push_back(queryPoints[i]);
                trainPts.push_back(trainPoints[i]);
            }
        }

        if(trainPts.size() >=4 && (queryPts.size() == trainPts.size())){
            H_Q2T = findHomography(queryPts, trainPts);
        }
    }
}

Mat getHomography(Mat& trainImg, Mat& queryImg){
    Rect rect(0, 0, trainImg.cols, queryImg.rows);
    return getHomography(trainImg, queryImg, rect);
}

Mat getHomography(Mat& trainImg, Mat& queryImg, Rect rect) {
    Mat H;
    Feature train = Feature();
    train.loadImg(trainImg);
    train.detectAndCompute();

    Feature query = Feature();
    query.loadImg(queryImg);
    query.detectAndCompute();

    Matcher m = Matcher(train, query);
    if(m.getQueryKeyPoints().size() == 0)
        return H;
    m.match();
    m.filterMatches();
    vector<DMatch> matches = m.getFilteredMatches();
    vector<Point2f> queryPoints;
    vector<Point2f> trainPoints;
    for (int i = 0; i < matches.size(); i++) {
        Point2f trainPt = m.getTrainKeyPoints()[matches[i].trainIdx].pt;
        if(rect.contains(Point((int)trainPt.x, (int)trainPt.y))){
            queryPoints.push_back(m.getQueryKeyPoints()[matches[i].queryIdx].pt);
            trainPoints.push_back(m.getTrainKeyPoints()[matches[i].trainIdx].pt);
        }
    }

    cout << "计算单应矩阵用到的匹配点数: " << queryPoints.size() << endl;
    if((trainPoints.size() >= 4) && (trainPoints.size() == queryPoints.size())){
        H = findHomography(trainPoints, queryPoints);
    }
    return H;
}

void testMatch(string trainImgPath, string queryImgPath) {
    Feature query;
    query.loadImg(queryImgPath);
    query.detectAndCompute();

    Feature train;
    train.loadImg(trainImgPath);
    train.detectAndCompute();

    Matcher m = Matcher(query, train);
    m.match();
    m.keepGoodMatches(2);
    m.filterMatches();
    m.drawFilteredMatches();
    waitKey(0);
}

void testHomography() {
    Mat train = imread("train2.jpg");
    Mat query = imread("query2.jpg");
    Rect rect = Rect(232, 872, (559-232), (1195-872));
}

//int main() {
//    testHomography();
//    return 0;
//}
