// Writes to the screen the first n Fibonacci numbers
// It illustrates the usage of a static variable
#include <iostream>
#include <math.h> 
#include <stdio.h> 

int fibonacci();
int main()
{
    int n,i;
    double golden_ratio;
    int fb[1000];
    
    printf("How many Fiboncci numbers ? \n ");
    scanf("%d",&n);
    printf("The first %d Fibonacci numbers are :\n",n);
    
    for(i=1;i<=n;i++)
    {
        fb[i]=fibonacci();
        printf("%d \t",fb[i]);

        if (i > 1) 
        {
        	//dd=tab[-1];
        	golden_ratio=(double)fb[i]/ (double)fb[i-1];
        	printf("%g \n", golden_ratio);
       	}
    }
	printf(" \n");

    return 0;
}
int fibonacci()
{
    static int _call = 0;
    static int f0=0, f1=1;
    int f2;
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
