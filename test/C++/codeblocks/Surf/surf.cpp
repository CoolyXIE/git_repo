#include "cv.h"
#include "highgui.h"
int main() {
    IplImage* img = cvLoadImage("test.jpg");
    cvNamedWindow( "test", 0 );
    cvShowImage("test", img);
    cvWaitKey(0);
    cvReleaseImage( &img );
    cvDestroyWindow( "test" );
    return 0;
}










//void surfdetect(IplImage *image1,IplImage *image2)
//{
//	using namespace std;
//	//IplImage *image1,*image2;
//	//image1 = cvLoadImage("lena1.jpg");
//	//image2= cvLoadImage("lena2.jpg");
//
//	cv::SurfFeatureDetector detector;
//	cv::SurfDescriptorExtractor descriptor_extractor;
//	cv::BruteForceMatcher<cv::L2<float>> descriptor_matcher;
//
//	//��ȡ������
//	std::vector<cv::KeyPoint> keypoints1,keypoints2;
//	detector.detect( image1,keypoints1);//���img1�е�Surf�����㣬�洢��keypoints1��
//	detector.detect( image2, keypoints2 );
//	cout<<"ͼ��1���������:"<<keypoints1.size()<<endl;
//	cout<<"ͼ��2���������:"<<keypoints2.size()<<endl;
//
//	//����������������������Ӿ��󣬼�������������
//	cv::Mat descriptors1,descriptors2;
//	descriptor_extractor.compute( image1, keypoints1, descriptors1 );
//	descriptor_extractor.compute( image2, keypoints2, descriptors2 );
//
//	cv::Mat img_keypoints1,img_keypoints2;
//	drawKeypoints(image1,keypoints1,img_keypoints1);
//	drawKeypoints(image2,keypoints2,img_keypoints2);
//	//imshow("Src1",img_keypoints1);
//	//cv::waitKey(6000);
//	//imshow("Src2",img_keypoints2);
//	//cv::waitKey(6000);
//
//	std::vector<cv::DMatch> matches;//ƥ����
//	descriptor_matcher.match( descriptors1, descriptors2, matches );//ƥ������ͼ�����������
//	cout<<"Match������"<<matches.size()<<endl;
//	cv::Mat img_matches1,img_matches2;
//	cv::drawMatches(image1,keypoints1,image2,keypoints2,matches,img_matches1);
//	imshow("��ƥ��",img_matches1);
//	cv::waitKey(0);
//
//	double max_dist = 0;
//	double min_dist = 100;
//	for(int i=0; i<matches.size(); i++)
//	{
//        double dist = matches[i].distance;
//        if(dist < min_dist) min_dist = dist;
//        if(dist > max_dist) max_dist = dist;
//        }
//    cout<<"�����룺"<<max_dist<<endl;
//    cout<<"��С���룺"<<min_dist<<endl;
//
//    //ɸѡ���Ϻõ�ƥ���
//    std::vector<cv::DMatch> goodMatches;
//    for(int i=0; i<matches.size(); i++)
//    {
//        if(matches[i].distance < 0.05 * max_dist)
//        {
//            goodMatches.push_back(matches[i]);
//        }
//    }
//    cout<<"goodMatch������"<<goodMatches.size()<<endl;
//    cv::drawMatches(image1,keypoints1,image2,keypoints2,goodMatches,img_matches2);
//    imshow("��ƥ��",img_matches2);
//    cv::waitKey(00);
//}

