/// standard headers
#include <iostream>						/// standard input/output library
#include <vector>						/// allows to use the vector class, (enhanced arrays)	
#include <stdlib.h> 					/// defines four variable types, several macros, and various functions
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
///namespaces
using namespace cv;
using namespace std;


void Sqrt_spiral(int &iterations, Mat &output)
//draws the Square root spiral to the screen
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

int main(int argc, char const *argv[])
{
/// constructs Sierpenski gasket by copying the 
    Mat img(600,600,CV_8U, Scalar(255));

	int nbr_iter;
	cout << "Enter number of iterations: " << endl;
	cin>> nbr_iter ;

	Sqrt_spiral(nbr_iter,img);
	imshow("Result", img);
	waitKey(0);	

    return 0;
}
