/*
	Project 4-2
	Reverse a string in place
*/
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int len;
	char str[] = "This Is A Test";
	char *start, *end;
	char t;

	cout << "Original string: " << str << "\n";
	len=strlen(str);
	start=str;
	end=&str[len-1];
	while(start<end) 
	{
		t=*start;
		*start = *end;
		*end=t;
		start++;
		end--;
	}
	cout << "Using pointers: " << str;
	return 0;
}
