// Writes to the screen the tent transformation sequence
// demonstrates a onestep machine based on a combined formula

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

const int width=400;
const int height=400;

 

int main()
{
	Mat img(height,width,CV_8U, Scalar(255));;
  
	// Three vertices(tuples) of the triangle  
	Point2i p1(300, 125) ;
	Point2i p2(200, 0) ;
	Point2i p3(100, 125); 
   // two extreme points of the Koch kernel
  	Point2i p4(0, 125); 
  	Point2i p5(400, 125); 
	// Drawing the triangle with the help of lines 
	//  on the black window With given points  
	// cv2.line is the inbuilt function in opencv library 
	line(img, p1, p2, (255, 0, 0), 1) ;
	line(img, p2, p3, (255, 0, 0), 1) ;
	line(img, p4, p3, (255, 0, 0), 1) ;
 	line(img, p5, p1, (255, 0, 0), 1) ; 
	// finding centroid using the following formula 
	// (X, Y) = (x1 + x2 + x3//3, y1 + y2 + y3//3)  
	Point2d centroid  ((p1.x+p2.x+p3.x)/3, (p1.y+p2.y+p3.y)/3); 
  
	// Drawing the centroid on the window   
	circle(img, centroid, 4, (255)) ;
  
	// image is the title of the window 
	imshow("image", img) ;
	waitKey(0) ;
    return 0;
}
