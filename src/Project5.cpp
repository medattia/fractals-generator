/*
	Project 4-1
	Demonstrate the bubble sort algorithm
*/

#include <iostream>
#include <cmath>
using namespace std;

// The Bubble Sort implementation
/*void BubbleSort(int table[], int size)
{
	int t,a,b;
	for(a=1; a<size; a++)
	{
		for(b=size-1; b>=a; b--)
		{
			if(table[b-1] > table[b]) 
			{
				t=table[b-1];
				table[b-1]=table[b];
				table[b]=t;
			}
		}
	}
}*/
int main()
{
	int nums[10];
	int a, b, t;
	int size;
	int *ptr;
	
	size=10;
	
	//let's put some random values in the array
	for (int i=0;i<size;i++) 
	{
		nums[i]=rand();
		cout << "Original value of num["<<i<<"]" << nums[i]  << endl;
	}
	ptr=nums;
	
	//BubbleSort(nums[],size);
	
	for(a=1; a<size; a++)
	{
		for(b=size-1; b>=a; b--)
		{
			if(nums[b-1] > nums[b]) 
			{
				t=nums[b-1];
				nums[b-1]=nums[b];
				nums[b]=t;
			}
		}
	}
	
	for (int i=0;i<size;i++) 
	{
		cout << "Sorted table's value of num["<<i<<"]" << nums[i]  << endl;
	}
	return 0;
}

