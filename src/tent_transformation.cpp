// Writes to the screen the tent transformation sequence

#include <iostream>
double fibonacci();
int main()
{
    int A,i;
    printf("Arbitrary positive integer \n");
    scanf("%d",&A);
    while (A>1)
    {
        if(A%2 == 0) A=A/2;
        else A=3*A+1;
        std::cout<<A<<endl;
    }
    return 0;
}
