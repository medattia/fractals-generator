/*
	Project 6-0
	A program to concatenate two strings
	A customized version of strcat()
	advantage in overloading a function
*/

#include <iostream>
#include <cstring>
using namespace std;
void mystrcat(char *s1, char *s2, int len=0);

int main()
{
	char str1[50] = "This is a test";
	char str2[50] = " and this is the second part";
	
	mystrcat(str1, str2, 5);// concat 5 characters
	cout<< str1 << '\n';
	
	strcpy(str1,"This is a test");
		
	mystrcat(str1, str2);// concat 5 characters
	cout<< str1 << '\n';
	
	return 0;
}


// A customized version of strcat()
void mystrcat(char *s1, char *s2, int len)
{
	int t,a,b;
	//find end of s1
	while(*s1) s1++;
	
	if(len==0) len = strlen(s2);
	
	while(*s2 && len)
	{
		*s1=*s2;
		s1++;
		s2++;
		len--;
	}
	*s1 = '\0'; // null terminate the string
}


