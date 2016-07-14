#include "Shape.h"
#include <vector>
#include <math.h>
#include "Basic.h"
const double max_double = (numeric_limits<double>::max)();
const double min_double = (numeric_limits<double>::min)();

using namespace std;
using namespace cv;

//MyPoint-自定义点
MyPoint2f::MyPoint2f(float x, float y) {
    this->x = x;
    this->y = y;
}

double MyPoint2f::getModule() const {
    return sqrt(x * x + y * y);
}

bool MyPoint2f::operator<(const MyPoint2f &mpt1) const {
    if (getModule() < mpt1.getModule())
        return true;
    else
        return false;
}

//Line-线段
Line::Line(Point2f beginPoint, Point2f endPoint) {
    this->beginPoint = beginPoint;
    this->endPoint = endPoint;
    this->k = (endPoint.y - beginPoint.y) / (endPoint.x - beginPoint.x);
    this->b = k * beginPoint.x - beginPoint.y;
}

bool Line::isOnLine(Point2f p, double eps) {

    if(fabs(k * p.x - p.y + b) < eps)
        return true;
    else
        return false;
}

bool Line::isOnSameSide(Point2f p1, Point2f p2) {
    if((k * p1.x - p1.y + b) * (k * p2.x - p2.y + b) > 0)
        return true;
    else
        return false;
}

ostream &operator<<(ostream &os, const Line &l) {
    os << l.beginPoint << "==>" << l.endPoint << "\t";
    return os;
}

//Ellipse-椭圆
Ellipse::Ellipse(Point2f leftUp, Point2f rightDown) {
    if(leftUp.x > rightDown.x || leftUp.y > rightDown.y)
        cout << "错误:这不是图像的左上角和右下角的点" << endl;
    else {
        float width = rightDown.x - leftUp.x;
        float height = rightDown.y - leftUp.y;
        this->center.x = 0.5 * (leftUp.x + rightDown.x);
        this->center.y = 0.5 * (leftUp.y + rightDown.y);
        if (width >= height) {
            this->a = 0.5 * width;
            this->b = 0.5 * height;
            longAxisTheta = 0;
        } else {
            this->a = 0.5 * height;
            this->b = 0.5 * width;
            longAxisTheta = 90;
        }
    }
}

bool Ellipse::isEmpty() {
    if(a == 0 || b == 0)
        return true;
    else
        return false;

}

bool Ellipse::contains(Point2f pt) {
    if(this->longAxisTheta == 0) {
        if(pow((pt.x - center.x) / a, 2) + pow((pt.y - center.y) / b, 2) <= 1)
            return true;
        else
            return false;
    } else if(this->longAxisTheta == 90) {
        if(pow((pt.y - center.y) / a, 2) + pow((pt.x - center.x) / b, 2) <= 1)
            return true;
        else
            return false;
    } else {
        cout << "错误, 长轴方向既不在x轴上,也不在y轴上"<< endl;
        return false;
    }
}

Mat Ellipse::drawOnImg(Mat &img) {
    Mat out = img.clone();
    Point centerInt = Point((int)this->center.x, (int)this->center.y);
    cv::ellipse(out, centerInt, Size(a, b), this->longAxisTheta, 0, 360, Scalar(255, 0, 0), 2, 8);
    showImg(out, "椭圆");
    return out;
}

//重载
ostream &operator<<(ostream &os, const Ellipse &e){
    os << "center: " << e.center << "\t";
    os << "a: " << e.a << "\t b: " << e.b << "\t长轴为: ";
    if (e.longAxisTheta == 0)
        os << "X轴";
    else
        os << "Y轴";
    return os;
}

//Circle-圆
Circle::Circle(Point2f center, float radius) {
    this->center = center;
    this->radius = radius;
}

vector<Point> Circle::getContourPoints() {
    vector<Point> contour;
    int y0 = (int)(0.5 * sqrt(2) * radius);
    //0-45度角
    for(int y = 0; y <= y0; y ++) {
        int x = (int)sqrt(radius * radius - y * y);
        contour.push_back(Point(x, y));
    }

    //45-90度角
    for(int i = contour.size() - 2; i >= 0; i --) {
        contour.push_back(Point(contour[i].y, contour[i].x));
    }

    //第二象限
    for(int i = contour.size() - 2; i >= 0; i --) {
        Point p = contour[i];
        contour.push_back(Point(-1 * p.x, p.y));
    }

    //第三,四象限
    for(int i = contour.size() -2; i > 0; i --) {
        Point p = contour[i];
        contour.push_back(Point(p.x, -1 * p.y));
    }

    //加上中心点偏移
    for(int i = 0; i < contour.size(); i ++) {
        contour[i].x += (int)center.x;
        contour[i].y += (int)center.y;
    }
    return contour;
}

ostream & operator<<(ostream &os, const Circle &c) {
    os << c.center << ", r=" << c.radius << "\t";
    return os;
}

//Rectangle-矩形
Rectangle::Rectangle(vector<Point2f> &points) {
    this->points = points;
}

Rectangle::Rectangle(Rect &rect) {
    vector<Point2f> points;
    points.push_back(Point2f(rect.x, rect.y));
    points.push_back(Point2f(rect.x + rect.width - 1, rect.y));
    points.push_back(Point2f(rect.x + rect.width - 1, rect.y + rect.height - 1));
    points.push_back(Point2f(rect.x, rect.y + rect.height - 1));
    this->points = points;
}

double Rectangle::getArea() { //to-do
    return 0;
}

double Rectangle::getMaxEdgeLen() {
    double maxEdgeLen = 0;
    for (size_t i = 0; i < this->points.size(); i++) {
        Point2f p1 = this->points[i];
        Point2f p2 = this->points[(i + 1) % this->points.size()];
        double edge = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
        if (edge > maxEdgeLen)
            maxEdgeLen = edge;
    }
    return maxEdgeLen;
}

Mat Rectangle::drawOnImg(Mat &img, string title) {
    Mat out = img.clone();
    vector<vector<Point>> contours = {Point2f_toPoint(this->points)};
    drawContours(out, contours, -1, Scalar(0,0,255), 2);
    showImg(out, title);
    return out;
}


ostream & operator<<(ostream &os, const Rectangle &r) {
    for (int i = 0; i < r.points.size(); i++)
        os << r.points[i] << "\t";
    return os;
}

//Polygon-多边形
Polygon::Polygon(vector<Point2f> &points) {
    this->points = points;
}

double Polygon::getArea() { //to-do
    return 0;
}

double Polygon::getMinEdge() {
    vector<double> edges = getAllEdges();
    return *min_element(edges.begin(), edges.end());
}

double Polygon::getMaxEdge() {
    vector<double> edges = getAllEdges();
    return *max_element(edges.begin(), edges.end());
}

vector<Point2f> &Polygon::getAllPoints() {
    return this->points;
}

vector<double> Polygon::getAllEdges() {
    vector<double> edges;
    for (int i = 0; i < this->points.size(); i++) {
        Point p1 = this->points[i];
        Point p2 = this->points[(i + 1) % this->points.size()];
        double edgeLen = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
        edges.push_back(edgeLen);
    }
    return edges;
}

vector<double> Polygon::getAllAngles() {
    vector<double> angles;
    for (int i = 0; i < this->points.size(); i ++) {
        Point2f center = this->points[i];
        Point2f left = this->points[(i-1+this->points.size()) % this->points.size()];
        Point2f right = this->points[(i+1) % this->points.size()];
        double angleInDegree = calAngleInDegree(left, center, right);
        angles.push_back(angleInDegree);
    }
    return angles;
}

vector<Point2f> Polygon::getIncludePixelsOfImg(Mat &img) {
    vector<Point2f> result;
    cv::Rect rect = cv::boundingRect(this->points);
    cout << rect.width * rect.height << endl;
    for(int i = rect.x; i < rect.x + rect.width; i ++) {
        for(int j = rect.y; j < rect.y + rect.height; j ++) {
            vector<Point2f> contour = this->points;
            Point2f pt = Point2f(i, j);
            if (pointPolygonTest(contour, Point2f(i,j), false) >= 0) {
                result.push_back(pt);
            }
        }
    }
    return result;
}

Mat Polygon::getIncludeImg(Mat &img) {
    Mat outImg = Mat::zeros(img.size(), img.type());
    Rect rect = boundingRect(this->points);
    vector<Point2f> contour = this->points;
    for (int i = rect.y; i < rect.y + rect.height; i++) {
        for (int j = rect.x; j < rect.x + rect.width; j++) {
            Point2f point = Point2f(j,i);
            if (pointPolygonTest(contour, point,0)>= 0)
                outImg.at<Vec3b>(i, j) = img.at<Vec3b>(i,j);
        }
    }
    return outImg;
}

Mat Polygon::drawOnImg(Mat &img, string title) {
    Mat out = img.clone();
    vector<vector<Point>> contours = {Point2f_toPoint(this->points)};
    drawContours(out, contours, -1, Scalar(0,0,255));
    showImg(out, title);
    return out;
}

bool Polygon::contains(Point pt){
    return this->contains(Point2f(pt.x, pt.y));
}

bool Polygon::contains(Point2f pt){
    if(pointPolygonTest(this->points, pt, false) > 0)
        return true;
    else
        return false;
}

ostream & operator<<(ostream &os, const Polygon &p) {
    for (int i = 0; i < p.points.size(); i++)
        os << p.points[i] << "\t";
    return os;
}

//test
void testGetIncludePixelsOfImg() {
    Mat img = imread("test2.jpg");
    Mat result = Mat(img.size(), CV_8UC3);
    vector<Point2f> points = {Point2f(39,49), Point2f(39,89), Point2f(56,89), Point2f(79,56)};
    Polygon polygon(points);
    cout << polygon << endl;
    Mat contourImg = img.clone();
    vector<Point2f> pixels = polygon.getIncludePixelsOfImg(img);
    cout << pixels.size() << endl;
    for(int i = 0; i < pixels.size(); i ++) {
        int row = (int)pixels[i].y;
        int col = (int)pixels[i].x;
        contourImg.at<Vec3b>(row, col) = {255, 0, 0};
    }
    Mat resultImg = polygon.drawOnImg(contourImg);
    showImg(resultImg);
    waitKey(0);
}

void testGetIncludeImg() {
    Mat img = imread("test3.jpg");
    vector<Point2f> points = {Point2f(52,76), Point2f(52,162), Point2f(135, 162), Point2f(135, 122)};
    Polygon polygon(points);
    Mat outImg = polygon.getIncludeImg(img);
    showImg(outImg);
    waitKey(0);
}

double calAngleInDegree(Point2f left, Point2f center, Point2f right) {
    double edge1 = sqrt(pow(left.x - center.x, 2) + pow(left.y - center.y, 2));
    double edge2 = sqrt(pow(right.x - center.x, 2) + pow(right.y - center.y, 2));
    double edge3 = sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2));

    double cosine = (pow(edge1, 2) + pow(edge2, 2) - pow(edge3, 2)) / (2 * edge1 * edge2);
    double angleInArc = acos(cosine);
    return angleInArc2Degree(angleInArc);
}

double calCosine(double angleInDegree) {
    return cos(angleInDegree2Arc(angleInDegree));
}

double angleInDegree2Arc(double angleInDegree) {
    return angleInDegree / 180 * pi;
}

double angleInArc2Degree(double angleInArc) {
    return angleInArc / pi * 180;
}












