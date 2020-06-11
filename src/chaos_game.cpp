// demonstrates the Chaos game 
#include <iostream>

#include <opencv2/opencv.hpp>

#define window_title "Iteration "

using namespace std;
using namespace cv;

struct Triangle
{
     Point2d a;
     Point2d b;
     Point2d c;
};

Point2d center(Point2d* a, Point2d* b)
{
    Point2d center_pt;
    center_pt=(*a+*b)/2.;
    return center_pt;
};

int main()
{
    int nbr;
    int max_iter=50000;
    struct Triangle trgl;
    Point2d current_pt(4.,4.);
    Point2d pt_1(0.,0.), pt_2(4.,0.), pt_3(2.,2.);
    Point2d pts[max_iter];
	Point2i int_pt;
	
	Mat img(800,1000,CV_8U, Scalar(255));;
    
    trgl.a=pt_1;
    trgl.b=pt_2;
    trgl.c=pt_3;

    for(int i=0;i<max_iter;i++)
    {
        pts[i]=current_pt;
		int_pt=(cv::Point_<int>) (current_pt*200);
        img.at<uchar>(int_pt) = 0;
        nbr = rand() % 3 + 1;
        switch (nbr)
        {
            case 1:
                current_pt=center(&current_pt,&pt_1);
            break;
            case 2:
                current_pt=center(&current_pt,&pt_2);
            break;
            case 3:
                current_pt=center(&current_pt,&pt_3);
            break;
        }
        //printf("pts[%d]:\n x=%g,\n y=%g. \n",i,current_pt.x,current_pt.y);
	   	namedWindow(window_title, WINDOW_AUTOSIZE);
		imshow(window_title, img);
		cv::waitKey(1);	
    }

	cv::destroyAllWindows();
    return 0;
}
