// draws the 3/2 curve 

#include <iostream>
#include <opencv2/opencv.hpp>

#define PI 3.14159265

using namespace cv;
using namespace std;

const int width=800;
const int height=400;


void koch_curve(Mat &input, Mat &output)// Point2d& points[])
{
    //place the first eigth
	input.copyTo(output.rowRange(output.rows/2-input.rows/2, output.rows/2+input.rows/2).colRange(0,input.cols));
	//place the eigth eigth
	input.copyTo(output.rowRange(output.rows/2-input.rows/2, output.rows/2+input.rows/2).colRange(output.cols-input.cols, output.cols));
    //place the 
    // get rotation matrix for rotating the image around its center in pixel coordinates
    /*cv::Point2f center((input.cols-1)/2.0, (input.rows-1)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, 90, 1.0); // angle =90°
    	imshow("rot", rot) ;
    // determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), input.size(), 90).boundingRect2f();
    // adjust transformation matrix
    rot.at<double>(0,2) += bbox.width/2.0 - input.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - input.rows/2.0;

    cv::Mat dst;
    cv::warpAffine(input, dst, rot, bbox.size());
    //crop image
    Range rows(14,dst.rows);
	Range cols(14,dst.cols);
	Mat croppedImage = dst(rows,cols);
	imshow("croppedImage", croppedImage) ;
	croppedImage.copyTo(output.rowRange(00, croppedImage.rows).colRange(90, 90+croppedImage.cols));   
	
	
	    // adjust transformation matrix

	flip(croppedImage,croppedImage, 1);
	croppedImage.copyTo(output.rowRange(00, croppedImage.rows).colRange(150, 150+croppedImage.cols));   
	*/
	return;
}

int main()
{
	Mat generator(height,width,CV_8U, Scalar(0));
  	Mat iter;
	// Points for the generator 

	Point2d p1(0,200);
	Point2d p2(200,200);
	Point2d p3(200,0); 
	Point2d p4(400,0);
	Point2d p5(400,200);
	Point2d p6(400,399); 
	Point2d p7(600,399);
	Point2d p8(600,200) ;
	Point2d p9(800,200); 
		Point2d points[9]={p1,p2,p3,p4,p5,p6,p7,p8,p9};
	// connectinct the points
	line(generator, p1, p2, (255, 255, 255), 1) ;
	line(generator, p2, p3, (255, 255, 255), 1) ;
	line(generator, p3, p4, (255, 255, 255), 1) ;
 	line(generator, p4, p5, (255, 255, 255), 1) ;   
	line(generator, p5, p6, (255, 255, 255), 1) ;
 	line(generator, p6, p7, (255, 255, 255), 1) ; 	
	line(generator, p7, p8, (255, 255, 255), 1) ;
 	line(generator, p8, p9, (255, 255, 255), 1) ; 

	// creating the generator iteration 0
	imshow("generator", generator) ;

	// iteraion 1	
	resize(generator, iter, Size(generator.cols/4, generator.rows/4), 0, 0, INTER_LINEAR);
		imshow("iter ", iter) ;
	koch_curve(iter,generator);
	imshow("iter 1", generator) ;
/*
	// iteraion 2	
	resize(generator, iter, Size(generator.cols/3, generator.rows/3), 0, 0, INTER_LINEAR);
	koch_curve(iter,generator);
	imshow("iter 1", generator) ;

	*/
			waitKey(0) ;
    return 0;
}
