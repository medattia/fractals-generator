/// standard headers
#include <iostream>						/// standard input/output library
#include <vector>						/// allows to use the vector class, (enhanced arrays)	
#include <stdlib.h> 					/// defines four variable types, several macros, and various functions
#include <type_traits>					/// defines a series of classes to obtain type information on compile-time.
#include <stdio.h>						/// C library to perform Input/Output operations
#include <time.h>						/// header declares the structure tm for time types
#include <ctime>						/// contains functions to get and manipulate date and time information.
#include <cmath>						/// contains several functions to manipulate C strings and arrays
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

int width=600;
int height=600;
void sierpensky(Mat &small, Mat &big)
// places ascaled down pattern into the input image
{
	small.copyTo(big.rowRange(0,height/3).colRange(0,width/3));
	small.copyTo(big.rowRange(0,height/3).colRange(width/3,2*width/3));
	small.copyTo(big.rowRange(0,height/3).colRange(2*width/3,width));
	small.copyTo(big.rowRange(height/3,2*height/3).colRange(0,width/3));
	small.copyTo(big.rowRange(height/3,2*height/3).colRange(2*width/3,width));
	small.copyTo(big.rowRange(2*height/3,height).colRange(0,width/3));
	small.copyTo(big.rowRange(2*height/3,height).colRange(width/3,2*width/3));
	small.copyTo(big.rowRange(2*height/3,height).colRange(2*width/3,width));
}

int main(int argc, char const *argv[])
{
/// constructs Sierpenski gasket by copying the 
    Mat img, img_iter,aux;
	Mat base(height,width,CV_8U, Scalar(0));

	Mat white_rec(height/3,width/3,CV_8U, Scalar(255));
	// build the kernel elements
	white_rec.copyTo(base.rowRange(height/3,2*width/3).colRange(height/3,2*width/3));

	int nbr_iter;
	cout << "Enter number of iterations: " << endl;
	cin>> nbr_iter ;
	
	namedWindow(window_title, WINDOW_AUTOSIZE);
	imshow(window_title, base);
	waitKey(0);	
	
	img_iter=base;

	for(int i=1;i<=nbr_iter;i++)
	{
		resize(img_iter, aux, Size(height/3,width/3), 0, INTER_LINEAR);
		sierpensky(aux,img_iter);
		imshow(to_string (i),img_iter);
		waitKey(0);	
        destroyWindow(to_string (i));
	}
	destroyAllWindows();
    return 0;
}
