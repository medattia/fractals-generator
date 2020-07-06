// draws the Koch curve 

#include <iostream>
#include <opencv2/opencv.hpp>

#define PI 3.14159265

using namespace cv;
using namespace std;

const int width=300;
const int height=89;


void koch_curve(Mat &input, Mat &output)
{
	input.copyTo(output.rowRange(output.rows-input.rows, output.rows).colRange(0,input.cols));
	input.copyTo(output.rowRange(output.rows-input.rows, output.rows).colRange(output.cols-input.cols, output.cols));

    // get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((input.cols-1)/2.0, (input.rows-1)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, 60, 1.0); // angle =60°
    cv::Mat rot2 = cv::getRotationMatrix2D(center, 300, 1.0); // angle =300°
    // determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), input.size(), 60).boundingRect2f();
    // adjust transformation matrix
    rot.at<double>(0,2) += bbox.width/2.0 - input.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - input.rows/2.0;

    cv::Mat dst;
    cv::warpAffine(input, dst, rot, bbox.size());
    //crop image
    Range rows(14,dst.rows);
	Range cols(14,dst.cols);
	Mat croppedImage = dst(rows,cols);

	croppedImage.copyTo(output.rowRange(00, croppedImage.rows).colRange(90, 90+croppedImage.cols));   
	
	
	    // adjust transformation matrix

	flip(croppedImage,croppedImage, 1);
	croppedImage.copyTo(output.rowRange(00, croppedImage.rows).colRange(150, 150+croppedImage.cols));   
	return;
}

void koch_island(Mat &input, Mat &output)
{
	// construct upper part
    Range rows(0,input.rows/2+10);
	Range cols(0,input.cols);
	Mat croppedImage = input(rows,cols);
	croppedImage.copyTo(output.rowRange(0, croppedImage.rows).colRange(0, output.cols));
	// construct lower part
	Point2f croppedcenter(croppedImage.cols/2.0F, croppedImage.rows/2.0F);	
	Mat rot_mat = getRotationMatrix2D(croppedcenter, 180, 1.0);
	Mat dst;
	warpAffine(croppedImage, dst, rot_mat, croppedImage.size());
	dst.copyTo(output.rowRange(output.rows/2+1, output.rows).colRange(0, output.cols));
	return;
}

int main()
{
	Mat generator(height,width,CV_8U, Scalar(0));
  	Mat iter;
	// Three vertices(tuples) of the triangle  
	Point2d p1(200, sin(PI/3)*100) ;
	Point2d p2(150, 0) ;
	Point2d p3(100, sin(PI/3)*100); 
   // two extreme points of the Koch kernel
  	Point2d p4(0, sin(PI/3)*100); 
  	Point2d p5(300, sin(PI/3)*100); 
	// Drawing the triangle with the help of lines 
	//  on the black window With given points  
	line(generator, p1, p2, (255, 255, 255), 1) ;
	line(generator, p2, p3, (255, 255, 255), 1) ;
	line(generator, p4, p3, (255, 255, 255), 1) ;
 	line(generator, p5, p1, (255, 255, 255), 1) ;   
	
	// creating the generator iteration 0
	imshow("generator", generator) ;
	// iteraion 1	
	resize(generator, iter, Size(generator.cols/3, generator.rows/3), 0, 0, INTER_LINEAR);
	koch_curve(iter,generator);
	imshow("iter 1", generator) ;

	// iteraion 2	
	resize(generator, iter, Size(generator.cols/3, generator.rows/3), 0, 0, INTER_LINEAR);
	koch_curve(iter,generator);
	imshow("iter 2", generator) ;
		Mat island (height+20,width,CV_8U, Scalar(0));
	koch_island(generator, island)		;
		imshow("island", island) ;
	// iteraion 3	
	resize(generator, iter, Size(generator.cols/3, generator.rows/3), 0, 0, INTER_LINEAR);
	koch_curve(iter,generator);
	imshow("iter 3", generator) ;
	waitKey(0) ;
    return 0;
}
