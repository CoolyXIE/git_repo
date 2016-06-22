
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<time.h>
#include<iostream>
using namespace std;
using namespace cv;



//暴力匹配算法,选择最为“可能”匹配的场景
int BruteForceMatch(Mat descriptor, vector<Mat> matDescribe, float min_dist)
{
	vector<DMatch> matches;
	int nEPointId = -1;
	BFMatcher matcher;
	for (int i = 0; i < matDescribe.size(); i++)
	{
		matches.clear();
		matcher.match(descriptor, matDescribe[i], matches);

		float avg_dist = 0.0;
		cout << "现在是第" << i+1 << "幅图，" << "匹配子数量是：" << matches.size() << endl;
		for (int j = 0; j < matches.size(); j++)
		{
			avg_dist += matches[j].distance;
			//cout << matches[j].distance << endl;
		}
		avg_dist /= matches.size();

		cout << "现在是第" << i+1 << "幅图，" << "对应的平均距离为：" << avg_dist << endl;
		if (min_dist > avg_dist)
		{
			min_dist = avg_dist;
			nEPointId = i;
		}
	}

	cout << "当前最小距离是" << min_dist << "第" << nEPointId + 1 << "场景最匹配";
	return nEPointId;

}


//移除NN比率大于阈值的匹配
int ratioTest(vector<vector<DMatch>>&matches, float ratio)
{
	int removed = 0;
	for (vector<vector<DMatch>>::iterator matchIterator = matches.begin(); matchIterator != matches.end(); ++matchIterator)
	{
		if (matchIterator->size() > 1)
		{
			if ((*matchIterator)[0].distance / (*matchIterator)[1].distance > ratio)
			{
				matchIterator->clear();
				removed++;
			}
		}
		else
		{
			matchIterator->clear();
			removed++;

		}
	}
	return removed;

}


//对称性筛选
void symmetryTset(vector<vector<DMatch>>&matches1, vector<vector<DMatch>>&matches2, vector<DMatch>&symMatches)
{
	//遍历图1到图2的所有匹配
	for (vector<vector<DMatch>>::iterator matchIterator1 = matches1.begin(); matchIterator1 != matches1.end(); ++matchIterator1)
	{
		if (matchIterator1->size() < 2)
			continue;
		//遍历图2到图1的所有匹配
		for (vector<vector<DMatch>>::iterator matchIterator2 = matches2.begin(); matchIterator2 != matches2.end(); ++matchIterator2)
		{
			if (matchIterator2->size() < 2)
				continue;
			if ((*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx && (*matchIterator2)[0].queryIdx == (*matchIterator1)[0].trainIdx)
			{

				symMatches.push_back(DMatch((*matchIterator1)[0].queryIdx, (*matchIterator1)[0].trainIdx, (*matchIterator1)[0].distance));
				break;
			}
		}

	}
}





void main()
{
	//计时
	double start1 = clock();
	//载入多张已建模图像
	Mat img1 = imread("4.jpg");
	Mat img2 = imread("6.jpg");
	Mat img3 = imread("1.jpg");
	vector<Mat> mat_All;
	mat_All.push_back(img1);
	mat_All.push_back(img2);
	mat_All.push_back(img3);
	//载入当前场景图像
	Mat imgTest = imread("5.jpg");
	Ptr<Feature2D> m_f2d = xfeatures2d::SURF::create();

	vector<vector<KeyPoint>> tempKeypoint;
	vector<Mat> matDescribe;

	vector<KeyPoint> keyPoint;
	Mat descriptor;

	//计算建模图像的特征点和描述子

	for (int i = 0; i < mat_All.size(); i++)
	{
		m_f2d->detectAndCompute(mat_All[i], noArray(), keyPoint, descriptor);
		tempKeypoint.push_back(keyPoint);
		matDescribe.push_back(descriptor);
	}

	//计算当前场景图像的特征点和描述子
	float min_dist = 10;
	vector<KeyPoint>  keyPointTest;
	Mat descriptorTest;
	m_f2d->detectAndCompute(imgTest, noArray(), keyPointTest, descriptorTest);
	int nEPointId = BruteForceMatch(descriptorTest, matDescribe, min_dist);
	double finish1 = clock();
	double  totaltime1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;   //这样就可以计算出来所耗费的时间，精确到毫秒级别
	cout << "匹配场景用时：" << totaltime1 << "秒" << endl;

	for (int j = 0; j < tempKeypoint.size(); j++)
	{
		cout << "第" << j << "幅图像特征点的数目是：" << tempKeypoint[j].size() << endl;

	}

	if (nEPointId != -1)
	{
		cout << "第" << nEPointId + 1 << "幅图像是可能的匹配场景" << endl;
		double start2 = clock();
		vector<DMatch> symMatches;
		vector<vector<DMatch>> knnmatches1, knnmatches2;
		BFMatcher matcher(NORM_L2);


		matcher.knnMatch(descriptorTest, matDescribe[nEPointId], knnmatches1, 2);

		matcher.knnMatch(matDescribe[nEPointId], descriptorTest, knnmatches2, 2);

		float Ratio = 0.5;
		int removed = ratioTest(knnmatches1, Ratio);
		cout << "Euery场景原来有" << knnmatches1.size() << "个匹配点，经过比率测试后，还剩" << knnmatches1.size() - removed << endl;
		removed = ratioTest(knnmatches2, Ratio);
		cout << "Train场景原来有" << knnmatches2.size() << "个匹配点，经过比率测试后，还剩" << knnmatches2.size() - removed << endl;
		symmetryTset(knnmatches1, knnmatches2, symMatches);

		double finish2 = clock();
		double  totaltime2 = (double)(finish2 - start2) / CLOCKS_PER_SEC;   //这样就可以计算出来所耗费的时间，精确到毫秒级别

		cout << "特征点匹配用时：" << totaltime2 << "秒" << endl;
		cout << "最终的匹配点数目是：" << symMatches.size() << endl;
		//画图
		cv::Mat img_matches;
		cv::drawMatches(imgTest, keyPointTest, mat_All[nEPointId], tempKeypoint[nEPointId], symMatches, img_matches);

		cv::drawKeypoints(imgTest, keyPointTest, imgTest, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::drawKeypoints(mat_All[nEPointId], tempKeypoint[nEPointId], mat_All[nEPointId], Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		cv::imshow("Surf-img1", imgTest);
		cv::imshow("Surf-img2", mat_All[nEPointId]);
		cv::imshow("Surf-Matches", img_matches); //highgui.hpp
		cv::waitKey(0);

	}
	else
		cout << "没有找到匹配的场景" << endl;

}

