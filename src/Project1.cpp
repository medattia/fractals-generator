/*
	Project 1-2
	This program displays a conversion table of feet to meters
*/

#include <iostream>
#define CONVERSION_CONSTANT 1/3.28
using namespace std;

int main()
{
	double *f_ptr; // holds the length in feet
	double *m_ptr; // holds the length in meters
	double table_f[100],table_m[100];
	f_ptr=table_f;
	m_ptr=table_m;
	for (int i=0; i<100 ; i++)
	{
		table_f[i]=(double)i;
		*m_ptr=*f_ptr*CONVERSION_CONSTANT;
		cout << *f_ptr << " " << *m_ptr << endl;
		f_ptr++;
		m_ptr++;
  	}

}
