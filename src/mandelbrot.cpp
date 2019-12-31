// creates
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

#include <fstream> // for files manipulation
#include <complex> // for complex numbers

#define window_title "Window"


using namespace cv;
using namespace std;



int main(int argc, char const *argv[])
{
    Mat img(300,300,CV_8U, Scalar(255));  
    
    int max_iteration=1000;
	int iteration;
	double x0=0.0;	//scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5,1))
	double y0=0.0;	//scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
	double x,y,xtemp;

	complex<float> z(0, 0);
	int rows=img.rows;
	int cols=img.cols;
	for (int i=0;i<rows;i++)
	{
		for (int j=0;j<cols;j++)
		{
			complex<float> pt((float)j/rows-1.5, (float)i/cols-0.5);
			x=(double) -j/40;
			y=(double) i/100;
			iteration=0;
			z = z * z + pt;
			while (abs (z) < 2/*while ((x*x + y*y < 4)*/ && iteration<max_iteration)
			{
				//xtemp=x*x-y*y+x0;
				//x=xtemp;
				iteration++;
			} 
			
			if(iteration<4) img.at<uchar>(j,i) = 0;
			/*else if((iteration>200) && (iteration<400))
			{
				img.at<uchar>(j,i) = 80;
			}
			else if((iteration>400) && (iteration<600))
			{
				img.at<uchar>(j,i) = 160;
			}
			else img.at<uchar>(j,i) = 220;*/
		}
	}	
	namedWindow(window_title, WINDOW_AUTOSIZE);
	imshow(window_title, img);
	waitKey(0);	
	destroyAllWindows();
    return 0;
}
/* this version doesn't use the opencv library
#include <iostream>
#include <fstream> // for files manipulation
#include <complex> // for complex numbersusing namespace std;

float width =  600;
float height = 600;

int value ( int x, int y)  {complex<float> point((float)x/width-1.5, (float)y/height-0.5);
// we divide by the image dimensions to get values smaller than 1
// then apply a translation
	complex<float> z(0, 0);
    unsigned int nb_iter = 0;
    while (abs (z) < 2 && nb_iter <= 34) {
           z = z * z + point;
           nb_iter++;
    }
    if (nb_iter < 34) return 255;
    else return 0;
}

int main ()  {
    ofstream my_Image ("mandelbrot.ppm"); 
    if (my_Image.is_open ()) {
        my_Image << "P3\n" << width << " " << height << " 255\n";
        for (int i = 0; i < width; i++) {
             for (int j = 0; j < height; j++)  {                  int val = value(i, j); 
                  my_Image << val<< ' ' << 0 << ' ' << 0 << "\n";
             }
        }
        my_Image.close();
    }
    else cout << "Could not open the file";
    return 0;
}

*/

