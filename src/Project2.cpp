/*
	Project 2-1
	Talking to Mars
*/

#include <iostream>
#define DISTANCE 34000000.0

using namespace std;

int main()
{
	const double lightspeed=186000.0; 
	double delay;
	double delay_in_min;
	
	delay=DISTANCE/lightspeed;
	cout << "Delay when talking to Mars is " << delay << endl;
	delay_in_min=delay/60;
	cout << "Delay when talking to Mars in minutes is " << delay_in_min << endl;
}
