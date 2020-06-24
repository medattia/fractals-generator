// Visualization of binary expansions by a two-branch tree

// constructs and visulize the Cantor set
#include <iostream>

#include <opencv2/opencv.hpp>

#define window_title "Iteration "

using namespace std;
using namespace cv;

struct Double_points
{
     Point2d a;
     Point2d b;
};

Double_points cantor(Point2d* a, Point2d* b)
{
    Double_points white_space;
    white_space.a=(*a+*b)/3.;
    white_space.b=(*a+*b)*2/3.;
    return white_space;
};

int main()
{
    int nbr;

    struct Double_points empty_space;
    Point2d point_a(0.,0.), point_b(3.,0.);
	Mat img(900,900,CV_8U, Scalar(255));;

	for(int r = 2; r < img.rows; r+=2)
	{
  		//for(int c = 0; c < m.cols; ++c)
        empty_space=cantor(point_a,point_b);
        for(int c = 2; r < img.rows; r+=2)
		pts[i]=current_pt;
		int_pt=(cv::Point_<int>) (current_pt*300);
        img.at<uchar>(int_pt) = 0;

	   	namedWindow(window_title, WINDOW_AUTOSIZE);
		imshow(window_title, img);
		cv::waitKey(1);	
    }

	cv::destroyAllWindows();
    return 0;
}
