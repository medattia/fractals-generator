// Writes to the screen the tent transformation sequence
// demonstrates a onestep machine based on a combined formula

#include <iostream>

int main()
{
    int A,i;
    printf("Arbitrary positive integer \n");
    scanf("%d",&A);
    while (A>1)
    {
        if(A%2 == 0) A=A/2;
        else A=3*A+1;
        std::cout<<A<<std::endl;
    }
    return 0;
}
