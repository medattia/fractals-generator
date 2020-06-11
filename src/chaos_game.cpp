// demonstrates the 
#include <iostream>
/// headers for openCV
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
///macros
#define window_title "Iteration "

//using namespace cv;
using namespace std;

struct Point
{
    double x;
    double y;  
};


struct Triangle
{
    struct Point a;
    struct Point b;
    struct Point c;
};


struct Point center(struct Point* a, struct Point* b)
{
    struct Point center_pt;
    center_pt.x=(a->x+b->x)/2;
    center_pt.y=(a->y+b->y)/2;
    return center_pt;
};
int main()
{
    int nbr;
    int max_iter=500000;
    struct Triangle trgl;
    struct Point current_pt;
    struct Point pt_1, pt_2, pt_3;
    struct Point pts[max_iter];
    
        cv::Mat img(800,1000,CV_8U, cv::Scalar(255));;
        
    pt_1.x = 0.;
    pt_1.y = 0.;
    pt_2.x = 4.;
    pt_2.y = 0.; 
    pt_3.x = 2.;
    pt_3.y = 2.;
    
    trgl.a=pt_1;
    trgl.b=pt_2;
    trgl.c=pt_3;
    
    current_pt.x=4.;
    current_pt.y=4.;
    int x_int, y_int;
    for(int i=0;i<max_iter;i++)
    {
        pts[i]=current_pt;
        x_int=(int) (current_pt.x*200);
		y_int=(int) (current_pt.y*200);
        img.at<uchar>(y_int,x_int) = 0;
        //printf("The current point is x=%g,y=%g \n ",current_pt.x,current_pt.y);
        nbr = rand() % 3 + 1;
        //printf("The dice roll yields %d \n ",nbr);
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
    }
    
    cv::namedWindow(window_title, cv::WINDOW_AUTOSIZE);
	cv::imshow(window_title, img);
	cv::waitKey(0);	
	cv::destroyAllWindows();
    return 0;
}
