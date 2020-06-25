// computes the coefficient of Pascal's triangle 
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

int main()
{
    int b[100000];
    int n;
	cout << "n ?" << endl ;
	cin >> n  ;
	for (int i=0; i<=n ; i++)
	{	
		for (int k = 0 ; k < i+1 ; k++) 
		{
			b[k]=(int) (tgamma(i+1)/(tgamma(k+1)*tgamma(i-k+1)));
    		printf(" %d ", b[k]); // using gamma function to compute n!= gamma(n+1)
		}
		printf("\n");
	}
    return 0;
}
