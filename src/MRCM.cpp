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

void MRCM(Mat &input, Mat &output)
{
	input.copyTo(output.rowRange(0, 200).colRange(150, 450));
	input.copyTo(output.rowRange(200, 400).colRange(0,300));
	input.copyTo(output.rowRange(200, 400).colRange(300,600));
}

int main(int argc, char const *argv[])
{
/// constructs Sierpenski gasket by copying the 
    Mat img, img_iter;
    String path("./test.png");
    
    img = imread(path,-1);
    //MRCM(im,res);

	Mat kernel(400,600,CV_8U, Scalar(255));
	// constituants
	Mat white_rec(200,300,CV_8U, Scalar(200)), black_rec(200,300,CV_8U, Scalar(0)), grey_rec(200,300,CV_8U, Scalar(122));
	
	// build the kernel elements
	black_rec.copyTo(kernel.rowRange(0, 200).colRange(150, 450));
	white_rec.copyTo(kernel.rowRange(200, 400).colRange(0,300));
	grey_rec.copyTo(kernel.rowRange(200, 400).colRange(300,600));

	int nbr_iter;
	cout << "Enter number of iterations: " << endl;
	cin>> nbr_iter ;
	
	namedWindow(window_title, WINDOW_AUTOSIZE);
	imshow(window_title, kernel);
	waitKey(0);	
	
	img_iter=kernel;
	
	for(int i=1;i<=nbr_iter;i++)
	{
		resize(img_iter, kernel, black_rec.size(), 0, 0, INTER_LINEAR);
		MRCM(kernel,img_iter);
		imshow(to_string (i), img_iter);
		waitKey(0);	
        destroyWindow(to_string (i));
	}
	destroyAllWindows();
    return 0;
}
