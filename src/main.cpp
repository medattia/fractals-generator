/// including headers
#include <iostream>		/// standard input/output library
#include <vector>		/// allows to use the vector class, (enhanced arrays)	
#include <stdlib.h> 	/// defines four variable types, several macros, and various functions
#include <type_traits>	/// defines a series of classes to obtain type information on compile-time.
#include <stdio.h>		/// C library to perform Input/Output operations
#include <time.h>		/// header declares the structure tm for time types
#include <ctime>		/// contains functions to get and manipulate date and time information.
#include <string>		/// contains several functions to manipulate C strings and arrays
/// headers for openCV
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>


#define window_title "Window"


using namespace cv;
using namespace std;

void MRCM(const Mat &input, Mat &output)
{
	input.copyTo(output.rowRange(0, 200).colRange(150, 450));
	input.copyTo(output.rowRange(200, 400).colRange(0,300));
	input.copyTo(output.rowRange(200, 400).colRange(300,600));
}

double sqrt_feedback_machine(const int &x0, int &a, int &iterations)
{
	double x[iterations];
	x[0]=x0;
		cout<<x0<<endl;
	for(int i=0;i<=iterations-1;i++)
	{
		x[i+1]=(x[i]+a/x[i])/2;
				cout<<x[i+1]<<endl;

	}
	return x[iterations];
}

int main(int argc, char const *argv[])
{
    Mat im, resized;
    String path("./test.png");
    im = imread(path,-1);
    //MRCM(im,res);
	Mat rest(400,600,CV_8U, Scalar(255));
	Mat res(200,300,CV_8U, Scalar(255));
	Mat result(100,150,CV_8U, Scalar(255));
	// constutiant elements
	Mat white_rec(50,75,CV_8U, Scalar(200)),black_rec(50,75,CV_8U, Scalar(0)), grey_rec(50,75,CV_8U, Scalar(122));
	//first iteration
	black_rec.copyTo(result.rowRange(0, 50).colRange(37,112));
	white_rec.copyTo(result.rowRange(50, 100).colRange(0, 75));	
	grey_rec.copyTo(result.rowRange(50, 100).colRange(75, 150));	
	//second iteration
	result.copyTo(res.rowRange(0, 100).colRange(75, 225));
	result.copyTo(res.rowRange(100, 200).colRange(0,150));
	result.copyTo(res.rowRange(100, 200).colRange(150,300));
	//third iteration
	res.copyTo(rest.rowRange(0, 200).colRange(150, 450));
	res.copyTo(rest.rowRange(200, 400).colRange(0,300));
	res.copyTo(rest.rowRange(200, 400).colRange(300,600));
	
	resize(rest, resized, res.size(), 0, 0, INTER_LINEAR);
	MRCM(resized,rest);
	
	resize(rest, resized, res.size(), 0, 0, INTER_LINEAR);
	MRCM(resized,rest);

	resize(rest, resized, res.size(), 0, 0, INTER_LINEAR);
	MRCM(resized,rest);
		
	namedWindow(window_title, WINDOW_AUTOSIZE);
	imshow(window_title, result);
	waitKey(0);	
	imshow(window_title, res);
	waitKey(0);	
	imshow(window_title, rest);
	waitKey(0);	
	destroyAllWindows();
	int x0=2, a=2, iterations=2;
	double function_return;
	function_return=sqrt_feedback_machine(x0,a,iterations);
	cout<<function_return<<endl;
    return 0;
}
