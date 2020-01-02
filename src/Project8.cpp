/*
	Project 7-1
	Left and right rotate functions for byte values
*/

#include <iostream>
using namespace std;
unsigned char rrotate(unsigned char val, int n);
unsigned char lrotate(unsigned char val, int n);
void show_binary(unsigned int u);
int main()
{
	unsigned char c;
		cout<< sizeof(c) <<endl ;		
	c=c<<8; 
	cout<< sizeof(c) <<endl ;		
	return 0;
}

//show a binary representation of an unsigne integer u
void show_binary(unsigned int u)
{
	for(int t=128; t>0; t=t/2)
	{
		if(u & t) cout <<"1";
		else cout <<"0";
	}
};

//right rotate a byte n places
unsigned char rrotate(unsigned char val, int n)
{
}
