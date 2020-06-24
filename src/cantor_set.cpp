// constructs and visulize the Cantor set
#include <iostream>
#include <math.h>       /* pow */
#include <list>
#include <opencv2/opencv.hpp>

#define window_title "Iteration "

using namespace std;
using namespace cv;
#include <iostream>
 
const int cols = 720;
const int rows = 60;
 
char lines[cols*rows];
Mat img(rows,cols,CV_8U, Scalar(255));;
// recursive method needs to be changed
// use the code available at Rosetta code
void cantor(int start, int len, int index) 
{
	int seg = len / 3;
	if (seg == 0) return;
	for (int i = index; i < rows; i++) 
	{
		for (int j = start + seg; j < start + seg * 2; j++) // starts from the position of the white space 
		{
			int pos = i * cols + j;							// goes to the current position of white by skipping previous elements
			lines[pos] = ' ';					// places white		
			img.at<uchar>(pos) = 255;					
		}
	}
	cantor(start,           seg, index + 1);  	// apply on the left segment
	cantor(start + 2 * seg, seg, index + 1);	// apply on the right segment
}
 
int main() 
{
	// init
	for (int i = 0; i < cols*rows; i++) 
	{
		lines[i] = '*';
		img.at<uchar>(i) = 0;
	}
 
	// calculate
	cantor(0, cols, 1);
 
	// print
	for (int i = 0; i < rows*cols; i += cols) 
	{
		printf("%.*s\n", cols, lines + i);
	}
	   	namedWindow(window_title, WINDOW_AUTOSIZE);
		imshow(window_title, img);
		waitKey(0);
	//scv::destroyAllWindows();
	  			//cout << img << endl;
    return 0;
}
/*
class Node 
{ 
	public: 
    	int start; 
    	int end; 
    	Node* next; 
}; 

// This function prints contents of linked list 
// starting from the given node 
void printList(Node* n) 
{ 
    while (n != NULL) { 
        cout << n->data << " "; 
        n = n->next; 
    } 
} 
https://www.geeksforgeeks.org/ternary-representation-of-cantor-set/
int main()
{
	Node* head = NULL; 
    Node* second = NULL; 
    Node* third = NULL; 
  
    // allocate 3 nodes in the heap 
    head = new Node(); 
    second = new Node(); 
    third = new Node(); 
  
  	head->start=0;
  	head->end=300;
  	head->next=second;

  	second->start=head->end/3;
  	second->head->start+second->start;
  	second->next=third;
  	
  	head->end=head->start+(head->end)/3;	   
    for(i=L.begin(); i!=L.end(); ++i) cout << *i << " ";
  
    int nbr;
    int pts[2000000];
    int current_pt, nbr_whites;
	int table[]=[
	Mat img(30,27,CV_8U, Scalar(255));;
	// intilizes the first row 
  	for(int c = 0; c < img.cols; c++)
  	{
  			img.at<uchar>(0,c) = 0;
  	}
  	int step, i;
	for(int r = 2; r < img.rows; r+=2)
	{
		step=r/2;

		cout << "Step= "<< step << endl;
  		for(int j=0; j<(pow(2,step)-1)*2; j++)  // iterates on the table of extreme points of a white space
  		{
  			pts[j]=(j+1)*27/pow(3,step);
			//cout << "pts[ "<< j << "]="  << pts[j] << endl;
  		}	
  		i=0;
  		for(int col = 0; col < img.cols; col++)
  		{
  			if ( col <= pts[i] or col >= pts[i+1] )
  			{
  			  	cout << "r ="<< r << "col =" <<  col << endl;
  				img.at<uchar>(r,col) = 0;
  							cout << "img.at<uchar>(r,c) ="<< img.at<uchar>(r,col) << endl;

  			}
  			i+=2;
  		}
 // 2^n intervals of length 1 / 3^n after the nth step        
// TODO construct a table containing the white space coordinates, incrementing it each time with the appropriate new whit space after each iteration (row skip)
        //printf("pts[%d]:\n x=%g,\n y=%g. \n",i,current_pt.x,current_pt.y);
	
    }
	   	namedWindow(window_title, WINDOW_AUTOSIZE);
		imshow(window_title, img);
		waitKey(0);
	//scv::destroyAllWindows();
	  			//cout << img << endl;
    return 0;
}*/
