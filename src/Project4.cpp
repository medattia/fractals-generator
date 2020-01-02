/*
	Project 2-3
	Compute the regular payments for a loan
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double payment, int_rate, principal, pay_per_year;
	int num_years;
	cout << "Enter principal: ";
	cin >> principal;
	
	cout << "Enter interest rate: ";
	cin >> int_rate;
	
	cout << "Enter number of payments per year: ";
	cin >> pay_per_year;

	cout << "Enter number of year: ";
	cin >> num_years;
	
	payment= int_rate*(principal/pay_per_year)/(1-(pow(int_rate/pay_per_year+1,-pay_per_year*(double)num_years)));
	
	cout << "Payment is: " << payment << endl;
}

