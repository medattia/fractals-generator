#include <iostream>


double sqrt_feedback_machine(const int &x0, int &a, int &iterations)
// Sumerian square root calculation technique
// This demonstrates a type of a One-Step feedback machine
// This is equally called Newton's method

{
	double x[iterations];
	x[0]=x0;
		cout<<x0<<endl;
	for(int i=0;i<=iterations-1;i++)
	{
		x[i+1]=(x[i]+a/x[i])/2;
				cout<<x[i+1]<<endl;

	}
	return x[iterations];
}
