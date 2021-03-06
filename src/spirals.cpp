/// standard headers
#include <iostream>						/// standard input/output library
#include <vector>						/// allows to use the vector class, (enhanced arrays)	
#include <math.h> 				
#include <type_traits>					/// defines a series of classes to obtain type information on compile-time.
#include <stdio.h>						/// C library to perform Input/Output operations
#include <time.h>						/// header declares the structure tm for time types
#include <ctime>						/// contains functions to get and manipulate date and time information.
#include <string>						/// contains several functions to manipulate C strings and arrays
/// headers for openCV
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
///macros
#define window_title "Iteration "
#define PI 3.14
///namespaces
using namespace cv;
using namespace std;

void Archimedean_spiral(Mat &output)
{
	float x = 0;
	float y = 0;
	float angle = 0.0f;

	// Space between the spirals
	int a = 2, b = 2;

	for (int i = 0; i < 200; i++)
	{
		angle = 0.1 * i;
		x = (a + b * angle) * cos(angle);
		y = (a + b * angle) * sin(angle);
		Point2d pt(x,y);
		Point int_pt=(cv::Point_<int>) (pt*2);

		int_pt.x=int_pt.x+100;
		int_pt.y=int_pt.y+100;
				output.at<uchar>(int_pt) = 0;
		cout<<int_pt<<endl;
	}
}

void Logarithmic_spiral(Mat &output)
{
	double x = 0;
	double y = 0;
	double phi = 0.0;

	// Space between the spirals
	int a = 10.0f, k = 0.30f;

	for (int i = 0; i < 180; i++)
	{
		phi = ((2*PI)/180 ) * i;
		x = a*exp(k*phi)*cos(phi);
		y = a*exp(k*phi)*sin(phi);
		Point2d pt(x,y);
		cout<<pt<<endl;
		Point int_pt=(cv::Point_<int>) (pt);

		int_pt.x=int_pt.x+20;
		int_pt.y=int_pt.y+20;
		output.at<uchar>(int_pt) = 0;
		cout<<int_pt<<endl;
	}
}

void Sqrt_spiral(int &iterations, Mat &output)
//draws the Square root spiral to the screen
// implementation of pythagorean trees
{
	double length=output.cols/10;
	Point2d center(output.rows/2,output.cols/2);
	Point2d pt0(center.x, center.y - length); 
 	Point2d v;// vector going from center to point
 	Point2d pt;
 	pt=pt0;
 	line(output, center, pt, (0, 0, 0), 1) ; 
 	for (int i=1;i<iterations;i++)
 	{
 		v.x = pt.x - center.x; 
 		v.y = pt.y - center.y; 
 		//normalizing the vector
 		double mag = sqrt (v.x*v.x + v.y*v.y); 
 		v.x = v.x / mag; 
 		v.y = -v.y / mag;
 		double temp = v.x; 
 		v.x = v.y; 
 		v.y = temp;
 		Point2d new_pt;
 		new_pt.x = pt.x + v.x * length; 
 		new_pt.y = pt.y + v.y * length;
 		line(output, new_pt, pt, (0, 0, 0), 1) ; 
 		pt=new_pt;
 		line(output, center, pt, (0, 0, 0), 1) ; 
 	}
	return ;
}

void polygonal_spiral(Mat &output, int &iterations)
{
    int a=200;
	Point2d start(100,0);// first raw first column
    Point2d pt_right(0, 0); 
	Point2d pt_down(0, 0); 
    Point2d pt_down2(0, 0); 
    Point2d pt_left(0, 0);
    Point2d pt_left2(0, 0); 
    Point2d pt_up(0, 0);
    Point2d pt_up2(0, 0);
    	pt_right.x=start.x+a;
	    pt_right.y=start.y; 
	    pt_down.x=pt_right.x;
	    pt_down.y=pt_right.y+a; 
	    a=a/2;
	    pt_down2.x=pt_down.x;
	    pt_down2.y=pt_down.y+a;
	    pt_left.x=pt_down2.x-a;
	    pt_left.y=pt_down2.y; 
	    a=2*a/3;
	    pt_left2.x=pt_left.x-a;
	    pt_left2.y=pt_left.y; 
	    pt_up.x=pt_left2.x;
	    pt_up.y=pt_left2.y-a; 
	    a=3*a/4;
	    pt_up2.x=pt_up.x;
	    pt_up2.y=pt_up.y-a; 
   
        line(output, start, pt_right, (0, 0, 0), 1) ; 
        line(output, pt_right, pt_down, (0, 0, 0), 1) ; 
     	line(output, pt_down, pt_down2, (0, 0, 0), 1) ; 
     	line(output, pt_down2, pt_left, (0, 0, 0), 1) ; 
        line(output, pt_left, pt_left2, (0, 0, 0), 1) ;    
        line(output, pt_left2, pt_up, (0, 0, 0), 1) ;    
        line(output, pt_up, pt_up2, (0, 0, 0), 1) ;    
    for (int i=2;i<iterations;i++)
 	{
	    a=4*a/5;
        cout<<a<< endl;
 		start = pt_up2; 
    	pt_right.x=start.x+a;
	    pt_right.y=start.y; 
	    pt_down.x=pt_right.x;
	    pt_down.y=pt_right.y+a; 
	    a=5*a/6;
	    pt_down2.x=pt_down.x;
	    pt_down2.y=pt_down.y+a;
	    pt_left.x=pt_down2.x-a;
	    pt_left.y=pt_down2.y; 
	    a=6*a/7;
	    pt_left2.x=pt_left.x-a;
	    pt_left2.y=pt_left.y; 
	    pt_up.x=pt_left2.x;
	    pt_up.y=pt_left2.y-a; 
	    a=7*a/8;
	    pt_up2.x=pt_up.x;
	    pt_up2.y=pt_up.y-a; 
        line(output, start, pt_right, (0, 0, 0), 1) ; 
        line(output, pt_right, pt_down, (0, 0, 0), 1) ; 
     	line(output, pt_down, pt_down2, (0, 0, 0), 1) ; 
     	line(output, pt_down2, pt_left, (0, 0, 0), 1) ; 
        line(output, pt_left, pt_left2, (0, 0, 0), 1) ;    
        line(output, pt_left2, pt_up, (0, 0, 0), 1) ;    
        line(output, pt_up, pt_up2, (0, 0, 0), 1) ;    
 	}
	return ;
}

int main(int argc, char const *argv[])
{
	Mat img(400,600,CV_8U, Scalar(255));
	Mat img2(400,600,CV_8U, Scalar(255));

	int nbr_iter;
	cout << "Enter number of iterations: " << endl;
	cin>> nbr_iter ;

	Sqrt_spiral(nbr_iter,img);
	imshow("Result", img);
	
	waitKey(0);	
	Archimedean_spiral(img);	
	
	namedWindow(window_title, WINDOW_AUTOSIZE);
	imshow(window_title, img);
	waitKey(0);	
	
	Logarithmic_spiral(img);	
	
	namedWindow(window_title, WINDOW_AUTOSIZE);
	imshow(window_title, img);
	waitKey(0);	
	
	polygonal_spiral(img2,nbr_iter);	
	imshow("polygonal_spiral", img2);
	waitKey(0);		


    return 0;
}
