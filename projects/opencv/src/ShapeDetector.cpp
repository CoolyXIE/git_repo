#include <opencv.hpp>
#include<core/core.hpp>
#include<highgui/highgui.hpp>
#include<imgproc/imgproc.hpp>
#include "ShapeDetector.h"
//#include "Common.h"
#include <math.h>
#include <set>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

////Line
Line::Line(Point beginPoint, Point endPoint) {
	this->beginPoint = beginPoint;
	this->endPoint = endPoint;
}

//Circle
Circle::Circle(Point2f center, float radius) {
	this->center = center;
	this->radius = radius;
}

ostream & operator<<(ostream &os, const Circle &c) {
	os << c.center << ", r=" << c.radius << "\t";
	return os;
}

//Rectangle
Rectangle::Rectangle(vector<Point> &points) {
	this->points = points;
}

ostream & operator<<(ostream &os, const Rectangle &r) {
	for (int i = 0; i < r.points.size(); i++)
		os << r.points[i] << "\t";
	return os;
}

//Polygon
Polygon::Polygon()
{

}

Polygon::Polygon(vector<Point> &points) {
	this->points = points;
}
//get方法
vector<Point> &Polygon::getAllPoints() {
	return this->points;
}
//按顺序返回所有的边长
vector<double> Polygon::getAllEdgesLen() {
	vector<double> edges;
	for (int i = 0; i < this->points.size(); i++) {
		Point p1 = this->points[i];
		Point p2 = this->points[(i + 1) % this->points.size()];
		double edgeLen = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
		edges.push_back(edgeLen);
	}
	return edges;
}
//返回最小的边长
double Polygon::getLeastEdgeLen() {
	vector<double> edges = getAllEdgesLen();
	return *min_element(edges.begin(), edges.end());
}
//重载输出运算符
ostream & operator<<(ostream &os, const Polygon &p) {
	for (int i = 0; i < p.points.size(); i++)
		os << p.points[i] << "\t";
	return os;
}

//ShapeDetector类
//inner function


//构造函数
ShapeDetector::ShapeDetector() {
	//ctor
}

ShapeDetector::ShapeDetector(Mat &img) {
	this->img = img;
}

ShapeDetector::~ShapeDetector() {
	//dtor
}

//detect检测形状函数
vector<Line> ShapeDetector::detectLinesByHough() {
	//转化为灰度图
	Mat grayImg;
	cvtColor(this->img, grayImg, CV_BGR2GRAY);

	//先做边缘检测
	Mat cannyImg;
	Canny(grayImg, cannyImg, 50, 200);

	//做霍夫线变换
	vector<Vec4i> points;
	HoughLinesP(cannyImg, points, 1, CV_PI / 180, 80, 50, 10);

	vector<Line> lines;
	for (int i = 0; i < points.size(); i++) {
		Vec4i line = points[i];
		Point beginPoint = { line[0], line[1] };
		Point endPoint = { line[2], line[3] };
		Line l = Line(beginPoint, endPoint);
		lines.push_back(l);
	}
	return lines;
}

vector<Circle> ShapeDetector::detectCirclesByHough(double threRatio) {
	Mat matImageSrc = this->img.clone();
	Mat matImageGray, matImageFilter;
	cvtColor(matImageSrc, matImageGray, CV_BGR2GRAY);
	GaussianBlur(matImageGray, matImageFilter, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	HoughCircles(matImageFilter, circles, CV_HOUGH_GRADIENT, 1.5, 30, 200, 100, 0, 0);
	vector<Circle> vecCircles;
	Circle tempCircle(Point2f(0, 0), 0);
	for (int i = 0; i < circles.size(); i++) {
		tempCircle.center.x = circles[i][0];
		tempCircle.center.y = circles[i][1];
		tempCircle.radius = circles[i][2];
		vecCircles.push_back(tempCircle);

	}
	vector<Circle> resultCircle = opt3_mergeSimilarCircles(vecCircles, threRatio);
	return  resultCircle;
}

vector<Rectangle> ShapeDetector::detectRectanglesByContour(double biasAngle) {
	//先把四边形检测出来
	vector<Polygon> polygons = this->detectPolygonsByContour(4);
    cout << "检测出的四边形个数：" << polygons.size() << endl;
	double threshold = cos((90 - biasAngle) / 180.0 * 3.1415926);
	vector<Rectangle> rectangles;
    drawPolygons(polygons, Scalar(0,0,255), 2);
    waitKey(0);
	for (int i = 0; i < polygons.size(); i++) {
		//对于每个四边形，判断是否为满足角度条件
		vector<Point> approx = polygons[i].points;
		if (approx.size() == 4 && fabs(contourArea(Mat(approx))) > 10000 && isContourConvex(Mat(approx)))
		//if (approx.size() == 4)
		{
			double maxCosine = 0;
			for (int j = 0; j < 4; j++) {
				double cosine = fabs(angle(approx[j % 4], approx[(j + 1) % 4], approx[(j + 2) % 4]));
				maxCosine = MAX(maxCosine, cosine);
			}
			if (maxCosine < threshold) {
				Rectangle rect = Rectangle(approx);
				rectangles.push_back(rect);
			}
		}
	}
	return rectangles;
}

vector<Polygon> ShapeDetector::detectPolygonsByContour(int edges) {
	vector<Polygon> polygons;
	Mat grayImg;
	Mat cannyImg;
	Mat filterImg;
	cvtColor(this->img, grayImg, CV_BGR2GRAY);
	Canny(grayImg, cannyImg, 60, 240);
    namedWindow("Canny图", WINDOW_NORMAL);
    imshow("Canny图", cannyImg);
    waitKey(0);
	vector<vector<Point>> contours;
	findContours(cannyImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	Mat contourImg = this->img.clone();
    drawContours(contourImg, contours, -1, Scalar(0,0,255), 2);
    namedWindow("轮廓图", WINDOW_NORMAL);
    imshow("轮廓图", contourImg);
    waitKey(0);


	int areaTooSmall = 0;

	for (int i = 0; i < contours.size(); i++) {
		vector<Point> polygon;
		approxPolyDP(Mat(contours[i]), polygon, arcLength(Mat(contours[i]), true) * 0.02, true);
		if (polygon.size() >= edges) {
			Polygon targetPolygon = opt1_mergeSimilarPoint(Polygon(polygon), edges);
			if (targetPolygon.points.size() == edges){
                if (fabs(contourArea(Mat(targetPolygon.points))) > 1){
                    polygons.push_back(targetPolygon);
                } else {
                    areaTooSmall ++;
                }
			}
		}
	}
	cout << "排除了面积太小的多边形个数：" << areaTooSmall << endl;
	return opt2_mergeSimilarPolygons(polygons, edges);
}

double ShapeDetector::angle(Point pt1, Point pt0, Point pt2) {
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

//优化程序1
Polygon ShapeDetector::opt1_mergeSimilarPoint(Polygon srcPolygon, int expectEdges, double threRatio) {
	vector<Point> points = srcPolygon.points;
	vector<double> edgeVec = srcPolygon.getAllEdgesLen();


	//找出第n大的边的边长
	double topNEdge;
	vector<double> sortedEdges = edgeVec;
	nth_element(sortedEdges.begin(), sortedEdges.begin() + expectEdges - 1, sortedEdges.end());
	topNEdge = sortedEdges[expectEdges - 1];
	double threshold = topNEdge * threRatio;

	//合并所有边长比topN的边长的threshold值还小的边
	vector<Point> newPolygon;
	//第i条边是第i个点和第i+1个点的连线
	vector<Point> mergedPoints;
	vector<Point> firstMergedPoints;

	bool lastEdgeIsSamll = false;
	for (int i = 0; i < edgeVec.size(); i++) {
		double e = edgeVec[i];
		if (lastEdgeIsSamll) {
			mergedPoints.push_back(points[i]);
			if (e < threshold)
				lastEdgeIsSamll = true;
			else {
				lastEdgeIsSamll = false;
				Point2f mergedPoint = { 0,0 };
				for (int j = 0; j < mergedPoints.size(); j++) {
					mergedPoint.x += mergedPoints[j].x;
					mergedPoint.y += mergedPoints[j].y;
				}
				mergedPoint.x /= mergedPoints.size();
				mergedPoint.y /= mergedPoints.size();
				//尾部处理需要用到
				if (find(mergedPoints.begin(), mergedPoints.end(), points[0]) != mergedPoints.end())
					firstMergedPoints = mergedPoints;
				mergedPoints.clear();
				newPolygon.push_back(mergedPoint);
			}
		}
		else {
			if (e < threshold) {
				lastEdgeIsSamll = true;
				mergedPoints.push_back(points[i]);
			}
			else {
				newPolygon.push_back(points[i]);
			}
		}
	}
	//处理最后一条边留下的mergedPoints
	if (mergedPoints.size() != 0) { //说明之前的第0个点群和末尾应该聚合
		Point mergedPoint = { 0,0 };
		for (int i = 0; i < mergedPoints.size(); i++) {
			mergedPoint.x += mergedPoints[i].x;
			mergedPoint.y += mergedPoints[i].y;
		}

		if (firstMergedPoints.size() == 0) { //第0个点群只有该点
			firstMergedPoints.push_back(points[0]);
		}
		int len = mergedPoints.size() + firstMergedPoints.size();
		for (int j = 0; j < firstMergedPoints.size(); j++) {
			mergedPoint.x += firstMergedPoints[j].x;
			mergedPoint.y += firstMergedPoints[j].y;
		}
		mergedPoint.x /= len;
		mergedPoint.y /= len;
		//新点应该放在新多边形的第0个点
		newPolygon[0] = mergedPoint;
	}
	return Polygon(newPolygon);
}

//需要的函数
bool isInclude(vector<int> vec, int num) {
	bool res = false;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == num) {
			res = true;
			break;
		}
	}
	return res;
}

void detectAndChangeClusters(vector<vector<int>> &clusters, int i, int j) {
	int flag = 0;
	for (int k = 0; k < clusters.size(); k++) {
		if (isInclude(clusters[k], i) && !isInclude(clusters[k], j)) {
			clusters[k].push_back(j);
			flag = 1;
			break;
		}

		if (!isInclude(clusters[k], i) && isInclude(clusters[k], j)) {
			clusters[k].push_back(i);
			flag = 1;
			break;
		}
		if (isInclude(clusters[k], i) && isInclude(clusters[k], j)) {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		vector<int> v;
		v.push_back(i);
		v.push_back(j);
		clusters.push_back(v);
	}
}

vector<Polygon> ShapeDetector::opt2_mergeSimilarPolygons(vector<Polygon> srcPolygons, int edges, double threRatio) {
	vector<vector<int>> clusters;

	for (int i = 0; i < srcPolygons.size() - 1; i++) {
		for (int j = i + 1; j < srcPolygons.size(); j++) {
			if (isSimilar(srcPolygons[i], srcPolygons[j], 0.2)) {
				detectAndChangeClusters(clusters, i, j);
			}
		}
	}

	vector<Point> averPoint(edges);
	vector<Polygon> resultPolygon;

	for (int m = 0; m < clusters.size(); m++) {
		//矫正
		for (int n = 1; n < clusters[m].size(); n++) {
			correctSimilarVertexOrder(srcPolygons[clusters[m][0]], srcPolygons[clusters[m][n]]);
		}
		//合并
		int sumX;
		int sumY;
		vector<Point> points;
		for (int k = 0; k < edges; k++) {
			sumX = 0;
			sumY = 0;
			for (int t = 0; t < clusters[m].size(); t++) {
				sumX += srcPolygons[clusters[m][t]].points[k].x;
				sumY += srcPolygons[clusters[m][t]].points[k].y;
			}
			Point p = Point(sumX / clusters[m].size(), sumY / clusters[m].size());
			//Point p.x = (int)sumX / clusters[m].size();
			//Point p.y = (int)sumY / clusters[m].size();
			points.push_back(p);
		}
		Polygon polygon = Polygon(points);
		resultPolygon.push_back(polygon);
	}

	//加入标号未进入clusters里面对应的多边形
	set<int> mergedIndexSet;
	for (int i = 0; i < clusters.size(); i++) {
		for (int j = 0; j < clusters[i].size(); j++) {
			mergedIndexSet.insert(clusters[i][j]);
		}
	}

	for (int i = 0; i < srcPolygons.size(); i++) {
		if (mergedIndexSet.find(i) == mergedIndexSet.end()) {
			resultPolygon.push_back(srcPolygons[i]);
		}
	}
    cout << "合并的多边形个数：" << srcPolygons.size() - resultPolygon.size() << endl;
	return  resultPolygon;
}

vector<Circle> ShapeDetector::opt3_mergeSimilarCircles(vector<Circle> curCircle, double threRatio) {
	vector<vector<int>> clusters;
	for (int i = 0; i < curCircle.size() - 1; i++) {
		for (int j = i + 1; j < curCircle.size(); j++) {
			if (isSimilar(curCircle[i], curCircle[j], threRatio))
				detectAndChangeClusters(clusters, i, j);
		}

	}


	vector<Circle> resultCricle;
	for (int m = 0; m < clusters.size(); m++) {
		int sumX = 0;
		int sumY = 0;
		int sumRadius = 0;
		vector<Point> points;

		for (int t = 0; t < clusters[m].size(); t++) {
			sumX += curCircle[clusters[m][t]].center.x;
			sumY += curCircle[clusters[m][t]].center.y;
			sumRadius += curCircle[clusters[m][t]].radius;
		}

		Circle c(Point2f(0, 0), 0);
		c.center.x = sumX / float(clusters[m].size());
		c.center.y = sumY / float(clusters[m].size());
		c.radius = sumRadius / float(clusters[m].size());

		resultCricle.push_back(c);
	}

	//加入标号未进入clusters里面对应的圆
	set<int> mergedIndexSet;
	for (int i = 0; i < clusters.size(); i++) {
		for (int j = 0; j < clusters[i].size(); j++) {
			mergedIndexSet.insert(clusters[i][j]);
		}
	}

	for (int i = 0; i < curCircle.size(); i++) {
		if (mergedIndexSet.find(i) == mergedIndexSet.end()) {
			resultCricle.push_back(curCircle[i]);
		}
	}
	return  resultCricle;


}

bool ShapeDetector::isSimilar(Polygon &polygon1, Polygon &polygon2, double threRatio) {
	double threshold = threRatio * std::min(polygon1.getLeastEdgeLen(), polygon2.getLeastEdgeLen());
	for (int i = 0; i < polygon1.points.size(); i++) {
		Point p1 = polygon1.points[i];
		double minDist = 10000;
		for (int j = 0; j < polygon2.points.size(); j++) {
			Point p2 = polygon2.points[j];
			double dist = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
			if (dist < minDist) {
				minDist = dist;
			}
		}
		//判断最小的距离是否小于阈值
		if (minDist >= threshold) {
			return false;
		}
	}
	return true;



}

bool ShapeDetector::isSimilar(Circle &circle1, Circle &circle2, double threRatio) {
	bool flag = false;
	//if(fabs(circle1.center.x- circle2.center.x)<threRatioCenter  && fabs(circle1.center.y - circle2.center.y) <threRatioCenter  && fabs(circle1.radius - circle2.radius)<threRatioRadius)
	if (sqrt((circle1.center.x - circle2.center.x)*(circle1.center.x - circle2.center.x) + (circle1.center.y - circle2.center.y)*(circle1.center.y - circle2.center.y)) < MIN(circle1.radius, circle2.radius)*threRatio)
		flag = true;
	return flag;
}

void ShapeDetector::correctSimilarVertexOrder(Polygon &model, Polygon &target) {
	Point modelP0 = model.points[0];
	Point modelP1 = model.points[1];
	//找到target中跟P0,P1对应的点的序号
	int index0;
	int index1;

	double minDist0 = 10000;
	double minDist1 = 10000;
	for (int i = 0; i < target.points.size(); i++) {
		Point p = target.points[i];
		double dist0 = sqrt(pow(p.x - modelP0.x, 2) + pow(p.y - modelP0.y, 2));
		double dist1 = sqrt(pow(p.x - modelP1.x, 2) + pow(p.y - modelP1.y, 2));
		if (dist0 < minDist0) {
			minDist0 = dist0;
			index0 = i;
		}
		if (dist1 < minDist1) {
			minDist1 = dist1;
			index1 = i;
		}
	}

	vector<int> replaceVec;
	//判断
	int N;
	if (model.points.size() == target.points.size())
		N = model.points.size();
	else
		cout << "错误：模板多边形和目标多边形大小不一样" << endl;

	if (index1 == (index0 + 1) % N) {
		for (int i = 0; i < N; i++) {
			replaceVec.push_back((index0 + i) % N);
		}
	}
	else if (index1 == (index0 - 1 + N) % N) {
		for (int i = 0; i < N; i++) {
			replaceVec.push_back((index0 - i + N) % N);
		}
	}
	else {
		cout << "错误：模板和目标多边形不匹配" << endl;
	}
	//开始修改target顺序
	vector<Point> newTargetPoints;
	for (int i = 0; i < replaceVec.size(); i++) {
		int targetIndex = replaceVec[i];
		//要把target多边形的第targetIndex个顶点改为第i个顶点
		newTargetPoints.push_back(target.points[targetIndex]);
	}
	target.points = newTargetPoints;
}

//draw
Mat ShapeDetector::drawRectangles(vector<Rectangle> &rectangles, Scalar color, int thickness) {
	Mat result = this->img.clone();
	vector<vector<Point>> contours;
	for (int i = 0; i < rectangles.size(); i++)
	{
		Rectangle rect = rectangles[i];
		vector<Point> contour;
		for (int j = 0; j < rect.points.size(); j++)
		{
			contour.push_back(rect.points[j]);
		}
		contours.push_back(contour);
	}
	drawContours(result, contours, -1, color, thickness);
	namedWindow("矩形", WINDOW_NORMAL);
	imshow("矩形",result);
	return result;
}

Mat ShapeDetector::drawPolygons(vector<Polygon> &polygons, Scalar color, int thickness)
{
	Mat result = this->img.clone();
	vector<vector<Point>> contours;
	for (int i = 0; i < polygons.size(); i++)
	{
		Polygon polygon = polygons[i];
		vector<Point> contour;
		for (int j = 0; j < polygon.points.size(); j++)
		{
			contour.push_back(polygon.points[j]);
		}
		contours.push_back(contour);
	}
	drawContours(result, contours, -1, color, thickness);
	namedWindow("多边形", WINDOW_NORMAL);
	imshow("多边形", result);
	return result;
}

Mat ShapeDetector::drawCircles(vector<Circle> &circles, Scalar color, int thickness) {
	Mat result = this->img.clone();
	for (int i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i].center.x), cvRound(circles[i].center.y));
		int radius = cvRound(circles[i].radius);
		//绘制圆心
		circle(result, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(result, center, radius, color, thickness);
	}
	namedWindow("圆", WINDOW_NORMAL);
	imshow("圆", result);
	return result;
}


void testCircle(string filePath) {
	Mat img = imread("圆\\" + filePath);
	while (img.rows > 1000 && img.cols > 1000) {
		resize(img, img, Size(img.cols/2, img.rows/2));
	}
	cout << "分辨率：" << img.cols << "*" << img.rows << endl;
	ShapeDetector s = ShapeDetector(img);
	vector<Circle> circles = s.detectCirclesByHough();
	cout << "圆形个数：" << circles.size() << endl;
	for (int i = 0; i < circles.size(); i++)
		cout << circles[i] << endl;
	Mat result = s.drawCircles(circles);
	imwrite("圆\\result_" + filePath, result);
}

void testRectangle(string filePath) {
	Mat img = imread("矩形\\" + filePath);
//	while (img.rows > 2000 && img.cols > 2000) {
//		resize(img, img, Size(img.cols/2, img.rows/2));
//	}
//    cout << "降低分辨率为: " << img.cols  << " * " << img.rows << endl;
	ShapeDetector s = ShapeDetector(img);
	vector<Rectangle> rects = s.detectRectanglesByContour();
	cout << "矩形数量是："<<rects.size() << endl;
	for (int i = 0; i < rects.size(); i++)
		cout << rects[i] << endl;
	Mat result = s.drawRectangles(rects);
	imwrite("矩形\\result_" + filePath, result);
}

//void testContour(string filePath)
//{
//	Mat img = imread("圆\\" + filePath);
//	while (img.rows > 1000 && img.cols > 1000) {
//		resize(img, img, Size(img.cols, img.rows));
//	}
//	Mat grayImg;
//	Mat cannyImg;
//	Mat result = img.clone();
//	cvtColor(img, grayImg, CV_BGR2GRAY);
//	//blur(grayImg, grayImg, Size(3, 3));
//	Canny(grayImg, cannyImg, 80, 240);
//	vector<vector<Point>> contours;
//	findContours(cannyImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//	drawContours(img, contours, -1, Scalar(255, 0, 0), 3);
//	imshow("resultContours", img);
//	waitKey(0);
//	imwrite("resultContours.jpg", img);
//
//}

void testTriangle(string filePath) {
	Mat img = imread("三角形\\" + filePath);
//	while (img.rows > 1000 && img.cols > 1000) {
//		resize(img, img, Size(img.cols, img.rows));
//	}
	ShapeDetector s = ShapeDetector(img);
	vector<Polygon> polygons = s.detectPolygonsByContour(3);
	cout << "三角形数量是：" << polygons.size() << endl;
	for (int i = 0; i < polygons.size(); i++)
		cout << polygons[i] << endl;
	Mat result = s.drawPolygons(polygons);
	imwrite("三角形\\result_" + filePath, result);
}

void testPolygon4(string filePath){
	Mat img = imread("四边形\\" + filePath);
//	while (img.rows > 1000 && img.cols > 1000) {
//		resize(img, img, Size(img.cols, img.rows));
//	}
	ShapeDetector s = ShapeDetector(img);
	vector<Polygon> polygons = s.detectPolygonsByContour(4);
	cout << "四边形数量是：" << polygons.size() << endl;
	for (int i = 0; i < polygons.size(); i++)
		cout << polygons[i] << endl;
	Mat result = s.drawPolygons(polygons);
	imwrite("四边形\\result_" + filePath, result);

}

void test(Mat img) {
	Mat matImageSrc = img.clone();
	Mat matImageGray, matImageFilter;
	cvtColor(matImageSrc, matImageGray, CV_BGR2GRAY);
	GaussianBlur(matImageGray, matImageFilter, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	HoughCircles(matImageFilter, circles, CV_HOUGH_GRADIENT, 1.5, 30, 200, 100, 0, 0);
	cout << circles.size() << endl;
}


void testMain() {
	double time = getTickCount();
	testCircle("16.jpg");
//	testRectangle(".jpg");
//    testTriangle("1.jpg");
//    testPolygon4("9.jpg");
    time = (getTickCount() - time) / getTickFrequency();
	cout << "Time:" << time;
	cout << endl;
	waitKey(0);
}
