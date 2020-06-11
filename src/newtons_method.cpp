#include <iostream>		

using namespace std;

double sqrt_feedback_machine(const int &x0, int &a, int &iterations)
// Computes the square root of a using a guess x0
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

int main(int argc, char const *argv[])
{
	int x0, a, iterations;
	cout << "Enter the number to squre: " << endl;
	cin>> a ;
	cout << "Enter the initial guess: " << endl;
	cin>> x0 ;	
	cout << "Enter the number of iterations: " << endl;
	cin>> iterations ;	
	
	double function_return;
	function_return=sqrt_feedback_machine(x0,a,iterations);
	cout<<function_return<<endl;
    return 0;
}
