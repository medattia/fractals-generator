// Writes to the screen the first n Fibonacci numbers
// It illustrates the usage of a static variable
// Approximates the Golden ratio
#include <iostream>
#include <math.h> 
#include <iomanip> // for std::setprecision()

unsigned long long int fibonacci();
int main()
{
    unsigned int n,i;
    long double golden_ratio;
    unsigned long long int fb[1000];
    
    printf("How many Fiboncci numbers ? \n ");
    scanf("%d",&n);
    printf("The first %d Fibonacci numbers are :\n",n);
    
    for(i=1;i<=n;i++)
    {
        fb[i]=fibonacci();
        std::cout << "\t" << fb[i] << std::endl;

        if (i > 1) 
        {
        	golden_ratio=(double)fb[i]/ (double)fb[i-1];
        	std::cout << std::setprecision(20); // show 16 digits of precision
        	std::cout << "\n" << golden_ratio << std::endl;
       	}
    }
	printf(" \n");

    return 0;
}
unsigned long long int fibonacci()
{
    static unsigned long long int _call = 0;
    static unsigned long long int f0=0, f1=1;
    unsigned long long int f2;
    if (_call<=1)
    {
        _call++;
        return _call-1; 
    }
    f2=f0+f1;
    f0=f1;
    f1=f2;
    return f2;
}
