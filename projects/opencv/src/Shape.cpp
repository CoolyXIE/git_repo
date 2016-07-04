//#include "Shape.h"
//#include <math.h>
//
//using namespace std;
//using namespace cv;
//
//const double PI = 3.1415926;
//
//double calAngleInArc(Point2f left, Point2f vertex, Point2f right){
//    double leftEdge = sqrt(pow(left.x - vertex.x, 2) + pow(left.y - vertex.y, 2));
//    double rightEdge = sqrt(pow(right.x - vertex.x, 2) + pow(right.y - vertex.y, 2));
//    double oppositeEdge = sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2));
//    return acos((pow(leftEdge, 2) + pow(rightEdge, 2) - pow(oppositeEdge, 2))/(2 * leftEdge * rightEdge));
//}
//
//double arc2Degree(double angleInArc){
//    return angleInArc / PI * 180;
//}
//
//
///* **************************************************************
//   ***************************Line*******************************
//   ***************************************************************/
//
//Line::Line(Point2f beginPoint, Point2f endPoint){
//    this->p1 = beginPoint;
//    this->p2 = endPoint;
//}
//
//double Line::getLength(){
//    return sqrt(pow(this->p1.x - this->p2.x, 2) + pow(this->p1.y - this->p2.y, 2));
//}
//
//double Line::getTheta(){
//    Point2f xAxisP = Point2f{this->p1.x + 1, this->p1.y};
//    double angle = arc2Degree(calAngleInArc(this->p2, this->p1, xAxisP));
//    if(this->p2.y > this->p1.y)
//        return angle;
//    else
//        return 360 - angle;
//}
//
//ostream &operator<<(ostream &os, const Line &line){
//    os << line.p1 << "==>" << line.p2;
//    return os;
//}
//
///* **************************************************************
//   ***************************Circle*****************************
//   **************************************************************/
//
//Circle::Circle(Point2f center, double radius){
//    this->center = center;
//    this->radius = radius;
//}
//
//double Circle::getArea(){
//    return PI * pow(radius, 2);
//}
//
//double Circle::getCircum(){
//    return 2 * PI * radius;
//}
//
//ostream &operator<<(ostream &os, const Circle &circle){
//    os << circle.center << ", r = " << circle.radius;
//    return os;
//}
//
///* **************************************************************
//   ***************************Polygon****************************
//   **************************************************************/
//
//Polygon::Polygon(vector<Point2f> vertices){
//    this->vertices = vertices;
//}
//
//vector<Point2f> &Polygon::getVertices(){
//    return this->vertices;
//}
//
//vector<double> Polygon::getEdges(){
//    vector<double> edges;
//	for (int i = 0; i < this->vertices.size(); i++) {
//		Point p1 = this->vertices[i];
//		Point p2 = this->vertices[(i + 1) % this->vertices.size()];
//		double edgeLen = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
//		edges.push_back(edgeLen);
//	}
//	return edges;
//}
//
//vector<double> Polygon::getAngles(){
//    vector<double> angles;
//    for(int i = 0; i < this->n; i ++){
//        Point2f vertex = this->vertices[i];
//        Point2f left = this->vertices[(i + this->n - 1)%this->n];
//        Point2f right = this->vertices[(i + 1) % this->n];
//        double angle = arc2Degree(calAngleInArc(left, vertex, right));
//        angles.push_back(angle);
//    }
//    return angles;
//}
//
//double Polygon::getArea(){
//    double area = 0;
//    for(int i = 0; i < this->n; i ++){
//        Point2f p1 = this->vertices[i];
//        Point2f p2 = this->vertices[(i+1)%this->n];
//        area += p1.x * p2.y - p2.x * p1.y;
//    }
//    return area * 0.5;
//}
//
//double Polygon::getCircum(){
//    vector<double> edges = this->getEdges();
//    double circum = accumulate(edges.begin(), edges.end(), 0);
//    return circum;
//}
//
//ostream &operator<<(ostream &os, const Polygon &polygon){
//    os << polygon.n << "边形:\t";
//    for(int i = 0; i < polygon.n; i ++)
//        os << polygon.vertices[i] << "\t";
//    return os;
//}
//
///* **************************************************************
//   ***************************Triangle****************************
//   **************************************************************/
//Triangle::Triangle(vector<Point2f> &vertices):Polygon(vertices){}
//
//bool Triangle::check(){
//    if(this->n == 3){
//        vector<double> edges = this->getEdges();
//        double e1 = edges[0];
//        double e2 = edges[1];
//        double e3 = edges[2];
//        if((e1+e2>e3) && (e1+e3>e2) && (e2+e3>e1))
//           return true;
//    }
//    return false;
//}
//
///* **************************************************************
//   ***************************Parallelogram**********************
//   **************************************************************/
//Parallelogram::Parallelogram(vector<Point2f> &vertices):Polygon(vertices){}
//
//bool Parallelogram::check(){
//    const double eps = 1e-3;
//    //对边相等，对角相等
//    vector<double> edges = this->getEdges();
//    vector<double> angles = this->getAngles();
//    if((fabs(edges[0] - edges[2]) < eps && fabs(edges[1] - edges[3]) < eps) && (fabs(angles[0] - angles[2]) < eps && fabs(angles[1] - angles[3] < eps)))
//        return true;
//    else
//        return false;
//}
//
///* **************************************************************
//   ***************************Rectangle**************************
//   **************************************************************/
//
////Rectangle::Rectangle(vector<Point2f> &vertices):Parallelogram(vertices){}
//
////bool Rectangle::check(){
////    const double eps = 1e-3;
////    const double biasDegree = 5;
////    vector<double> edges = this->getEdges();
////    vector<double> angles = this->getAngles();
////    if((fabs(edges[0] - edges[2]) < eps && fabs(edges[1] - edges[3]) < eps) && (fabs(angles[0] - angles[2]) < eps && fabs(angles[1] - angles[3] < eps)))
////
////}
//
//
//
//
//
//
//
