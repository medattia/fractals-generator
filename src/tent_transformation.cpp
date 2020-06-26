// Writes to the screen the tent transformation sequence
// demonstrates a onestep machine based on a combined formula

#include <iostream>
#include <cmath>
double tent_frac(double &input)
{
	double frac, intpart, output;
	frac = modf (input , &intpart);
	if (frac <=0.5) output=2*frac;
	else output=2*(1-frac);
	return output;
}

tent(int &input)
{
    while (input>1)
    {
        if(input%2 == 0) input=input/2;
        else input=3*input+1;
        std::cout<<input<<std::endl;
    }
}
int main()
{
    int A;
    double x;
    printf("Arbitrary positive integer \n");
    scanf("%d",&A);
    tent(A);
    x=0.142857143;
    std::cout<< tent_frac(x) <<std::endl;
    
    return 0;
}
