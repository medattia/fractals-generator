/*
	Project 2-2
	Creating an XOR using the C++ logical operators
*/

#include <iostream>
#include <cmath>
using namespace std;

void XOR(bool a, bool b)
{
	cout << a << "XOR" << b << "=" << ((a || b) && !(a && b)) << endl;
};
int main()
{
	XOR(true,true);
	XOR(true,false);
	XOR(false,true);
	XOR(false,false);
}
