// self explanatory
#include <iostream>

struct Point
{
    int x;
    int y;  
};


struct Triangle
{
    struct Point a;
    struct Point b;
    struct Point c;
};


struct Point center(struct Point* a, struct Point* b)
{
    struct Point res;
    res.x=a->x+b->x;
    res.y=a->y+b->y;
    return res;
};
int main()
{
    int nbr;
    int max_iter=100;
    struct Triangle t;
    struct Point current;
    struct Point a1, a2, a3;
    struct Point pts[max_iter];
    
    a1.x =-1;
    a1.y = 0;
    a2.x = 0;
    a2.y = 2; 
    a3.x = 1;
    a3.y = 0;
    
    t.a=a1;
    t.b=a2;
    t.c=a3;
    
    current.x=0;
    current.y=0;
    
    for(int i=0;i<max_iter;i++)
    {
        pts[i]=current;
        nbr = rand() % 3 + 1;
        switch (nbr)
        {
            case 1:
                current=center(&current,&a1);
            break;
            case 2:
                current=center(&current,&a2);
            break;
            case 3:
                current=center(&current,&a3);
            break;
        }
        printf("pts[%d]:\n x=%d,\n y=%d. \n",i,current.x,current.y);
    }
    
    return 0;
}
