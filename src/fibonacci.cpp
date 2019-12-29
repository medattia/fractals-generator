// Writes to the screen the first n Fibonacci numbers
// It illustrates the usage of a static variable
#include <iostream>
double fibonacci();
int main()
{
    int n,i;
    printf("How many Fiboncci numbers \n ?");
    scanf("%d",&n);
    printf("The first %d Fibonacci numbers are :\n",n);
    for(i=1;i<=n;i++)
    {
        double fb=fibonacci();
        printf("%g \t",fb);
    }
    //getch();
    return 0;
}
double fibonacci()
{
    static int _call = 0;
    static double f0=0, f1=1;
    double f2;
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
