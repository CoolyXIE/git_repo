#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "ShapeDetector.h"
#include "Basic.h"
#include "Camera.h"
#include "Shape.h"
#include <math.h>
#include <set>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

#define pi 3.1415926

ShapeDetector::ShapeDetector(Mat &img) {
    this->img = img.clone();
    this->angleBias = 8.0;
    this->pointDistRatio1 = 0.1;
    this->edgeDistRatio2 = 0.01;
    this->leastShapeArea = 30;
    this->insideRect = Rect(0, 0, img.cols, img.rows);
}

//set
void ShapeDetector::setAngleBias(double biasInDegree){
    this->angleBias = biasInDegree;
}

void ShapeDetector::setInsideRect(Rect insideRect){
    this->insideRect = insideRect;
}

void ShapeDetector::setOutsideRect(Rect outsideRect){
    this->outsideRect = outsideRect;
}

void ShapeDetector::setEdgeDistRatio2(double edgeDistRatio2){
    this->edgeDistRatio2 = edgeDistRatio2;
}

void ShapeDetector::setLeastShapeArea(double leastArea){
    this->leastShapeArea = leastArea;
}

void ShapeDetector::setPointDistRatio1(double pointDistRatio1){
    this->pointDistRatio1 = pointDistRatio1;
}





vector<Line> ShapeDetector::detectLinesByHough() {

    Mat grayImg;
    cvtColor(this->img, grayImg, CV_BGR2GRAY);
    Mat cannyImg;
    Canny(grayImg, cannyImg, 50, 200);
    vector<Vec4i> points;
    HoughLinesP(cannyImg, points, 1, CV_PI / 180, 80, 50, 10);

    vector<Line> lines;
    for (int i = 0; i < points.size(); i++) {
        Vec4i line = points[i];
        Point2f beginPoint = Point2f(line[0], line[1]);
        Point2f endPoint = Point2f(line[2], line[3]);
        Line l = Line(beginPoint, endPoint);
        lines.push_back(l);
    }
    return lines;
}

vector<Circle> ShapeDetector::detectCirclesByHough() {
    Mat matImageSrc = this->img.clone();
    Mat matImageGray, matImageFilter;
    cvtColor(matImageSrc, matImageGray, CV_BGR2GRAY);
    GaussianBlur(matImageGray, matImageFilter, Size(9, 9), 2, 2);
    vector<Vec3f> circles;
    HoughCircles(matImageFilter, circles, HOUGH_GRADIENT, 1.5, 30, 160, 100, 0, 0);
    vector<Circle> vecCircles;
    Circle tempCircle(Point2f(0, 0), 0);
    for (int i = 0; i < circles.size(); i++) {
        if (pi*circles[i][2] * circles[i][2] > this->leastShapeArea) {
            tempCircle.center.x = circles[i][0];
            tempCircle.center.y = circles[i][1];
            tempCircle.radius = circles[i][2];
            vecCircles.push_back(tempCircle);
        }
    }
    vector<Circle> resultCircle;
    resultCircle = opt3_mergeSimilarCircles(vecCircles);
    return  resultCircle;
}

vector<Circle> ShapeDetector::detectCirclesByContour(){
	Mat resultImg= this->img.clone();
	Mat grayImg;
	Mat filterImg;
	Mat cannyImg;
	cvtColor(this->img, grayImg, CV_BGR2GRAY);
	GaussianBlur(grayImg, filterImg, Size(9, 9), 2, 2);
	Canny(filterImg, cannyImg, 80, 240);

	vector<vector<Point>> contours;
	findContours(cannyImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	drawContours(resultImg, contours, -1, Scalar(255, 0, 0), 3);
	vector<Circle> vecCircles;
	for (int i = 0; i < contours.size(); i++)
	{
		Circle curcircle(Point2f(0, 0), 0);
		minEnclosingCircle(Mat(contours[i]), curcircle.center, curcircle.radius);
		vecCircles.push_back(curcircle);
	}
	vector<Circle> resultCircle;
	resultCircle = opt3_mergeSimilarCircles(vecCircles);
	return  resultCircle;
}

vector<Rectangle> ShapeDetector::detectRectanglesByContour(){
    //先把四边形检测出来
    vector<Polygon> polygons = this->detectPolygonsByContour(4);

    double threshold = cos((90 - this->angleBias) / 180.0 * 3.1415926);
    vector<Rectangle> rectangles;
    for (int i = 0; i < polygons.size(); i++) {
        //对于每个四边形，判断是否为满足角度条件
        vector<Point2f> approx = polygons[i].points;
        if (approx.size() == 4 &&
                Rectangle(approx).getMaxEdgeLen() > this->edgeDistRatio2 * MAX(this->img.cols, this->img.rows) &&
                isContourConvex(Mat(approx))) {
            double maxCosine = 0;
            for (int j = 0; j < 4; j++) {
                double cosine = fabs(calCosine(calAngleInDegree(approx[j % 4], approx[(j + 1) % 4], approx[(j + 2) % 4])));
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
    vector<Polygon> outPolygons;
    vector<Polygon> polygons;
    Mat grayImg;
    Mat cannyImg;
    cvtColor(this->img, grayImg, CV_BGR2GRAY);
    Canny(grayImg, cannyImg, 100, 240);

//    画Canny图
//    showImg(cannyImg, "Canny图");

    vector<vector<Point>> contours;
    findContours(cannyImg, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    Mat tmp;
    //画轮廓图
//    tmp = this->img.clone();
//    drawContours(tmp, contours, -1, Scalar(255,0,0), 2);
//    showImg(tmp, "轮廓图");

    //近似多边形图
    vector<vector<Point>> contoursPoly;
    for(int i = 0; i < contours.size(); i ++){
        vector<Point> points;
        approxPolyDP(Mat(contours[i]), points, arcLength(Mat(contours[i]), true) * 0.02, true);
        contoursPoly.push_back(points);
    }
//    tmp = this->img.clone();
//    drawContours(tmp, contoursPoly, -1, Scalar(255,0,0), 2);
//    showImg(tmp, "近似多边形图");

    //只取特定区域
//    limitContoursOutsideRect(contoursPoly);
//    limitContoursInsideRect(contoursPoly);
//    tmp = this->img.clone();
//    drawContours(tmp, contours, -1, Scalar(255,0,0), 2);
//    showImg(tmp, "特定区域");
//    waitKey(0);

    for (int i = 0; i < contoursPoly.size(); i++) {
        vector<Point> polygon;
        if (polygon.size() >= edges) {
            vector<Point2f> points = Point_toPoint2f(polygon);
            Polygon targetPolygon = opt1_mergeSimilarPoint(Polygon(points), edges);
            if (targetPolygon.points.size() == edges&& fabs(contourArea(Mat(targetPolygon.points))) > this->leastShapeArea) {
                polygons.push_back(targetPolygon);
            }
        }
    }

    outPolygons = opt2_mergeSimilarPolygons(polygons);
    opt4_filterSmallAngle(outPolygons);
    return outPolygons;
}

Polygon ShapeDetector::opt1_mergeSimilarPoint(Polygon srcPolygon, int expectEdges) {
    vector<Point2f> points = srcPolygon.points;
    vector<double> edgeVec = srcPolygon.getAllEdges();
    //找出第n大的边的边长
    double topNEdge;
    vector<double> sortedEdges = edgeVec;
    nth_element(sortedEdges.begin(), sortedEdges.begin() + expectEdges - 1, sortedEdges.end());
    topNEdge = sortedEdges[expectEdges - 1];
    double threshold = topNEdge * this->pointDistRatio1;

    //合并所有边长比topN的边长的threshold值还小的边
    vector<Point2f> newPolygon;
    //第i条边是第i个点和第i+1个点的连线
    vector<Point2f> mergedPoints;
    vector<Point2f> firstMergedPoints;

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
        } else {
            if (e < threshold) {
                lastEdgeIsSamll = true;
                mergedPoints.push_back(points[i]);
            } else {
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

void detectAndChangeClusters(vector<vector<int>> &clusters, int i, int j) {
    int flag = 0;
    for (int k = 0; k < clusters.size(); k++) {
        if ((find(clusters[k].begin(), clusters[k].end(), i) != clusters[k].end()) && find(clusters[k].begin(), clusters[k].end(), j) == clusters[k].end()) {
            clusters[k].push_back(j);
            flag = 1;
            break;
        }

        if ((find(clusters[k].begin(), clusters[k].end(), i) == clusters[k].end()) && find(clusters[k].begin(), clusters[k].end(), j) != clusters[k].end()) {
            clusters[k].push_back(i);
            flag = 1;
            break;
        }
        if((find(clusters[k].begin(), clusters[k].end(), i) != clusters[k].end()) && find(clusters[k].begin(), clusters[k].end(), j) != clusters[k].end()) {
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

//optimize
vector<Polygon> ShapeDetector::opt2_mergeSimilarPolygons(vector<Polygon> srcPolygons) {
    int edges = srcPolygons.size();
    vector<vector<int>> clusters;
    for (int i = 0; i < srcPolygons.size() ; i++) {
        if (i + 1 == srcPolygons.size())
            break;
        for (int j = i + 1; j < srcPolygons.size(); j++) {
            if (isSimilar(srcPolygons[i], srcPolygons[j])) {
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
        vector<Point2f> points;
        for (int k = 0; k < edges; k++) {
            sumX = 0;
            sumY = 0;
            for (int t = 0; t < clusters[m].size(); t++) {
                sumX += srcPolygons[clusters[m][t]].points[k].x;
                sumY += srcPolygons[clusters[m][t]].points[k].y;
            }
            Point2f p = Point2f(sumX / clusters[m].size(), sumY / clusters[m].size());
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
    return  resultPolygon;
}

vector<Circle> ShapeDetector::opt3_mergeSimilarCircles(vector<Circle> curCircle) {
    vector<vector<int>> clusters;
    //double time = getTickCount();
    for (size_t i = 0; i < curCircle.size() ; i++) {
        if (i + 1 == curCircle.size())
            break;
        else {
            for (int j = i + 1; j < curCircle.size(); j++) {
                //cout << "正在进行相似性判断" << endl;
                if (isSimilar(curCircle[i], curCircle[j])) {
                    //cout << "正在进行聚类分析" << endl;
                    detectAndChangeClusters(clusters, i, j);
                }

            }

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
    //time = (getTickCount() - time) / getTickFrequency();
    //cout << "相似圆合并时间:" << time;
    return  resultCricle;


}

void ShapeDetector::opt4_filterSmallAngle(vector<Polygon> &srcPolygons){
    vector<double> angles;
    vector<Polygon> outPolygons;
    for(int i = 0;i < srcPolygons.size(); i ++){
        angles = srcPolygons[i].getAllAngles();
        if(*min_element(angles.begin(), angles.end()) >= this->angleBias)
            outPolygons.push_back(srcPolygons[i]);
    }
    srcPolygons = outPolygons;
}

//util
bool ShapeDetector::isSimilar(Polygon &polygon1, Polygon &polygon2) {
    double threshold = this->edgeDistRatio2 * MIN(polygon1.getMinEdge(), polygon2.getMinEdge());
    for (int i = 0; i < polygon1.points.size(); i++) {
        Point p1 = polygon1.points[i];
        double minDist = (numeric_limits<double>::max)();
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

bool ShapeDetector::isSimilar(Circle &circle1, Circle &circle2) {
    bool flag = false;
    if (sqrt((circle1.center.x - circle2.center.x)*(circle1.center.x - circle2.center.x)
             + (circle1.center.y - circle2.center.y)*(circle1.center.y - circle2.center.y))
        < MAX(this->img.rows, this->img.cols)*this->pointDistRatio1
            &&fabs(circle1.radius-circle2.radius)<MIN(circle1.radius, circle2.radius)* this->edgeDistRatio2)
        flag = true;
    return flag;
}

void ShapeDetector::limitContoursInsideRect(vector<vector<Point>> &contours){
    vector<vector<Point>> outContours;
    for(int i = 0; i < contours.size(); i ++){
        bool isInside = false;
        for(int j = 0; j < contours[i].size(); j ++){
            Point pt = contours[i][j];
            if ((pt.x >= this->insideRect.x && pt.x < this->insideRect.x + this->insideRect.width) &&
                (pt.y >= this->insideRect.y && pt.y < this->insideRect.y + this->insideRect.height))
                isInside = true;
                break;
        }
        if(!isInside)
            outContours.push_back(contours[i]);
    }
    contours = outContours;
}

void ShapeDetector::limitContoursOutsideRect(vector<vector<Point>> &contours){
    vector<vector<Point>> outContours;
    for(int i = 0; i < contours.size(); i ++){
        bool isOutside = false;
        for(int j = 0; j < contours[i].size(); j ++){
            Point pt = contours[i][j];
            if ((pt.x < this->outsideRect.x || pt.x >= this->outsideRect.x + this->outsideRect.width) ||
                (pt.y < this->outsideRect.y || pt.y >= this->outsideRect.y + this->outsideRect.height))
                isOutside = true;
                break;
        }
        if(!isOutside)
            outContours.push_back(contours[i]);
    }
    contours = outContours;
}

void ShapeDetector::correctSimilarVertexOrder(Polygon &model, Polygon &target) {


    Point modelP0 = model.points[0];
    Point modelP1 = model.points[1];
    //找到target中跟P0,P1对应的点的序号
    int index0;
    int index1;

    double minDist0 = (numeric_limits<double>::max)();
    double minDist1 = (numeric_limits<double>::max)();
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
    } else if (index1 == (index0 - 1 + N) % N) {
        for (int i = 0; i < N; i++) {
            replaceVec.push_back((index0 - i + N) % N);
        }
    } else {
        cout << "错误：模板和目标多边形不匹配" << endl;
    }
    //开始修改target顺序
    vector<Point2f> newTargetPoints;
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
    for (int i = 0; i < rectangles.size(); i++) {
        Rectangle rect = rectangles[i];
        vector<Point> contour;
        for (int j = 0; j < rect.points.size(); j++) {
            contour.push_back(rect.points[j]);
        }
        contours.push_back(contour);
    }
    drawContours(result, contours, -1, color, thickness);
    namedWindow("矩形", WINDOW_NORMAL);
    imshow("矩形",result);
    return result;
}

Mat ShapeDetector::drawPolygons(vector<Polygon> &polygons, Scalar color, int thickness) {
    Mat result = this->img.clone();
    vector<vector<Point>> contours;
    for (int i = 0; i < polygons.size(); i++) {
        Polygon polygon = polygons[i];
        vector<Point> contour;
        for (int j = 0; j < polygon.points.size(); j++) {
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
    for (int i = 0; i < circles.size(); i++) {
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
    Mat img = imread("img\\circle\\" + filePath);
    ShapeDetector s = ShapeDetector(img);
    vector<Circle> circles = s.detectCirclesByHough();
    for (int i = 0; i < circles.size(); i++)
        cout << circles[i] << endl;
    Mat result = s.drawCircles(circles);
    imwrite("img\\circle\\result_" + filePath, result);
}

void testRectangle(string filePath) {
    Mat img = imread("img\\rect\\" + filePath);
    ShapeDetector s = ShapeDetector(img);
    vector<Rectangle> rects = s.detectRectanglesByContour();
    cout << "矩形数量是："<<rects.size() << endl;
    for (int i = 0; i < rects.size(); i++)
        cout << rects[i] << "\t面积:\t" << rects[i].getArea() << "\t最大边长:\t" << rects[i].getMaxEdgeLen() << endl;
    Mat result = s.drawRectangles(rects);
    imwrite("img\\rect\\result_" + filePath, result);
}

void testTriangles(string filePath) {
    Mat img = imread("img\\tri\\" + filePath);
    ShapeDetector s = ShapeDetector(img);
    vector<Polygon> polygons = s.detectPolygonsByContour(3);
    cout << "三角形数量是：" << polygons.size() << endl;
    for (int i = 0; i < polygons.size(); i++)
        cout << polygons[i] << endl;
    Mat result = s.drawPolygons(polygons);
    imwrite("img\\tri\\result_" + filePath, result);
}

//detect in real time
void detectRectangleRealTime(){
    Camera c;
    Mat img;
    while(true){
        img = c.getFrame();
        ShapeDetector s = ShapeDetector(img);
        vector<Rectangle> rects = s.detectRectanglesByContour();
        s.drawRectangles(rects);
        waitKey(100);
    }
}

void detectQuadrangleRealTime(){
    Camera c;
    Mat img;
    while(true){
        img = c.getFrame();
        resize(img, img, Size(img.cols/2, img.rows/2));
        ShapeDetector s = ShapeDetector(img);
        vector<Polygon> quads = s.detectPolygonsByContour(4);
        s.drawPolygons(quads);
        waitKey(100);
    }
}

