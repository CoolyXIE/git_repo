#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<time.h>
#include<iostream>
#include <stdio.h>
#include <io.h>
#include "DirHelper.h"
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>

using namespace std;
using namespace cv;

const int STANDARD_WIDTH = 320;
const int STANDARD_HEIGHT = 240;

//暴力匹配算法,选择最为“可能”匹配的场景
int BruteForceMatch(Mat descriptor, vector<Mat> matDescribe) {
    double start = clock();
    vector<DMatch> matches;
    int bestId = -1;
//	int secondBestId = -1;
    float min_dist = 99999;
    BFMatcher matcher;
    for (int i = 0; i < matDescribe.size(); i++) {
        matches.clear();
        matcher.match(descriptor, matDescribe[i], matches);

        float avg_dist = 0.0;
        //cout << "现在是第" << i << "幅图，" << "匹配子数量是：" << matches.size() << endl;

        for (int j = 0; j < matches.size(); j++) {
            avg_dist += matches[j].distance;
            //cout << matches[j].distance << endl;
        }
        avg_dist /= matches.size();

        //cout <<"现在是第" << i<<"幅图，"<<"对应的平均距离为：" << avg_dist << endl;
        if (avg_dist < min_dist) {
//			secondBestId = bestId;
//			secondMin_dist = min_dist;
            min_dist = avg_dist;
            bestId = i;
        }
//		else if (avg_dist < secondBestId)
//		{
        //		secondBestId = i;
//			secondMin_dist = avg_dist;
//		}

    }

    //cout << "当前最小距离是" << min_dist<<"第"<< nEPointId+1<<"场景最匹配";

//	cout << "暴力匹配找到最近model图片花费时间：" << (clock() - start) / CLOCKS_PER_SEC << "秒" << endl;
//	int best[2];
    //best[0] = bestId;
    //best[1] = secondBestId;
    return bestId;
}

//移除NN比率大于阈值的匹配
int ratioTest(vector<vector<DMatch>>&matches, float ratio) {
    int removed = 0;
    for (vector<vector<DMatch>>::iterator matchIterator = matches.begin(); matchIterator != matches.end(); ++matchIterator) {
        if (matchIterator->size() > 1) {
            if ((*matchIterator)[0].distance / (*matchIterator)[1].distance > ratio) {
                matchIterator->clear();
                removed++;
            }
        } else {
            matchIterator->clear();
            removed++;

        }
    }
    return removed;
}

//对称性筛选
void symmetryTset(vector<vector<DMatch>>&matches1, vector<vector<DMatch>>&matches2, vector<DMatch>&symMatches) {
    double start = clock();
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

Mat readImg(const string& imgPath) {
    Mat srcImg = imread(imgPath);
    int width = srcImg.cols;
    int height = srcImg.rows;
    Mat stdImg;
    Mat grayImg;
    if (width < height)
        resize(srcImg, stdImg, Size(STANDARD_HEIGHT, STANDARD_WIDTH), 0, 0);
    else
        resize(srcImg, stdImg, Size(STANDARD_WIDTH, STANDARD_HEIGHT), 0, 0);
    cvtColor(stdImg, grayImg, CV_BGR2GRAY);
    return grayImg;
}

void main2() {
    //变量定义
    const int BF_MATCH_MIN_DIST = 10;
    const float KNN_RATIO = 0.6;
    double start;


    //for (int i = 1; i <= 4; i++)
    //{


    //}

    //建模图像处理
    Mat model1 = readImg("resource/model1.jpg");
    Mat model2 = readImg("resource/model2.jpg");
    Mat model3 = readImg("resource/model3.jpg");

    vector<Mat> mat_All;
    vector<vector<KeyPoint>> keyPointModels;
    vector<Mat> describeModels;
    mat_All.push_back(model1);
    mat_All.push_back(model2);
    mat_All.push_back(model3);

    Ptr<Feature2D> m_f2d = xfeatures2d::SURF::create();
    vector<KeyPoint> keyPoint;
    Mat descriptor;
    for (int i = 0; i<mat_All.size(); i++) {
        m_f2d->detectAndCompute(mat_All[i], noArray(), keyPoint, descriptor);
        keyPointModels.push_back(keyPoint);
        describeModels.push_back(descriptor);
    }



    //计算建模图像的特征点和描述子





    //载入当前场景图像
    Mat testImg = readImg("resource/test.jpg");
    vector<KeyPoint>  keyPointTest;
    Mat descriptorTest;

    double start0 = clock();
    //计算当前场景图像的特征点和描述子
    start = clock();
    m_f2d->detectAndCompute(testImg, noArray(), keyPointTest, descriptorTest);
    cout << "Detect+Describe共花费 " << clock() - start << " ms";

//	cout << "计算test图像的描述子用时： " << (clock() - start) / CLOCKS_PER_SEC << "秒" << endl;
//	cout << "test描述子共有" << keyPointTest.size() << "个" << endl;

    start = clock();
    int matchId = BruteForceMatch(descriptorTest, describeModels);
    cout << "暴力匹配共花费" << clock() - start << " ms ";
    //int matchId1 = matchIdArr[0];
    //int matchId2 = matchIdArr[1];


    //if (true)
    if(matchId != -1)

    {
        //	cout << "model" << bestId + 1<< "是最匹配的图像"<< endl;
        //	cout << "model" << secondBestId + 1 << "是其次匹配的图像" << endl;

        //	for (int i = 0; i < 3; i++) {  //
        int i = matchId;
        vector<DMatch> symMatches;
        vector<vector<DMatch>> knnmatches1, knnmatches2;  //KNN匹配的结果
        BFMatcher matcher(NORM_L2);

        //knnMatch算法双向计算
        start = clock();
        matcher.knnMatch(descriptorTest, describeModels[i], knnmatches1, 2);
        //cout << "knn正向匹配用时： " << (clock() - start) / CLOCKS_PER_SEC << "秒" << endl;

        matcher.knnMatch(describeModels[i], descriptorTest, knnmatches2, 2);
        cout << "knn双向计算用时： " << clock() - start << " ms " << endl;

        //		cout << "正向KNNMatch有" << knnmatches1.size() << "个" << endl;
        //		cout << "反向KNNMatch有" << knnmatches2.size() << "个" << endl;

        //knnRatio筛选
        start = clock();
        int removedNum1 = ratioTest(knnmatches1, KNN_RATIO);
        int removedNum2 = ratioTest(knnmatches2, KNN_RATIO);

        cout << "KNNRatio筛选花费时间：" <<  clock() - start << "ms" << endl;
        //		cout << "正向移除了" << removedNum1 << "个.  反向移除了" << removedNum2 << endl;


        //对称性筛选
        start = clock();
        symmetryTset(knnmatches1, knnmatches2, symMatches);
        cout << "对称性筛选花费时间：" << clock() - start << " ms " << endl;
        cout << "最后与model" << i+ 1 << "匹配还剩最佳匹配点数为: " << symMatches.size() << endl;

        //计算bestId最终的剩余最佳匹配点数/test图像特征点的个数
        cout << "ratio" << i + 1<< " = " << symMatches.size() << '/' << keyPointTest.size() << " = " << symMatches.size() * 1.0 / keyPointTest.size() << endl;
        //	}


        //vector<DMatch> symMatchesS;
        //vector<vector<DMatch>> knnmatches1S, knnmatches2S;  //KNN匹配的结果

        //knnMatch算法双向计算
        //start = clock();
        //matcher.knnMatch(descriptorTest, describeModels[secondBestId], knnmatches1S, 2);
        //cout << "knn正向匹配用时： " << (clock() - start) / CLOCKS_PER_SEC << "秒" << endl;
        //start = clock();
        //matcher.knnMatch(describeModels[secondBestId], descriptorTest, knnmatches2S, 2);
        //cout << "knn逆向匹配用时： " << (clock() - start) / CLOCKS_PER_SEC << "秒" << endl;

        //cout << "正向KNNMatch有" << knnmatches1S.size() << "个" << endl;
        //cout << "反向KNNMatch有" << knnmatches2S.size() << "个" << endl;

        //knnRatio筛选
        //start = clock();
        //removedNum1 = ratioTest(knnmatches1S, KNN_RATIO);
        //removedNum2 = ratioTest(knnmatches2S, KNN_RATIO);
        //cout << "KNNRatio筛选花费时间：" << (clock() - start) / CLOCKS_PER_SEC << "秒" << endl;
        //cout << "正向移除了" << removedNum1 << "个.  反向移除了" << removedNum2 << endl;


        //对称性筛选
        //start = clock();
        //symmetryTset(knnmatches1S, knnmatches2S, symMatchesS);
        //cout << "对称性筛选花费时间：" << (clock() - start) / CLOCKS_PER_SEC << "秒" << endl;
        //cout << "最后还剩最佳匹配点数为: " << symMatchesS.size() << endl;

        //计算bestId最终的剩余最佳匹配点数/test图像特征点的个数
        //cout << "ratio1 = " << symMatchesS.size() << '/' << keyPointTest.size() << " = " << symMatchesS.size() * 1.0 / keyPointTest.size() << endl;


        //cout << "特征点匹配用时：" << totaltime2 << "秒" << endl;
        //cout << "最终的匹配点数目是：" << symMatches.size() << endl;
        //画图
        /*
        cv::Mat img_matches;
        cv::drawMatches(imgTest, keyPointTest, mat_All[nEPointId], tempKeypoint[nEPointId], symMatches, img_matches);

        cv::drawKeypoints(imgTest, keyPointTest, imgTest, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        cv::drawKeypoints(mat_All[nEPointId], tempKeypoint[nEPointId], mat_All[nEPointId], Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        cv::imshow("Surf-img1", imgTest);
        cv::imshow("Surf-img2", mat_All[nEPointId]);
        cv::imshow("Surf-Matches", img_matches); //highgui.hpp
        cv::waitKey(0);
        */

    } else
        cout << "没有找到匹配的场景" << endl;


    char buf[1];
    cin >> buf;
}

void getFiles(string path, vector<string>& files) {
    //文件句柄
    long   hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            //如果是目录,迭代之
            //如果不是,加入列表
            if ((fileinfo.attrib &  _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            } else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

int main() {
    string dirPath = "C:\\Users\\Administrator\\Desktop\\yl\\yl\\resource";
    DirHelper dirHelper = DirHelper(dirPath);
    Ptr<Feature2D> m_f2d = xfeatures2d::SURF::create();
    vector<string> files = dirHelper.getIncludeFiles(false);

    vector<string>::iterator iter;
    for (iter = files.begin(); iter != files.end(); iter++) {
        vector<KeyPoint> keyPoints;
        string fileName = *iter;
        Mat model = readImg(fileName);
        m_f2d->detect(model, keyPoints);
        cout << fileName << ":" << keyPoints.size() << endl;
    }




    int x;
    cin >> x;
    return x;
}
