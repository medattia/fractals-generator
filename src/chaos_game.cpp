// self explanatory

#include <iostream>

class Point
{
    public:
        Point(int,int); 
        int x;
        int y;
    
};

Point::Point(int a,int b)
{
    x=a;
    y=b;
}

class Triangle
{
    public:
        point a;
        point b;
        point c;
};

point center(point a, point b);
{
}
int main()
{
    int nbr;
    Triangle t;
    Point current;
    Point a1(-1,0), a2(0,2), a3(1,0);
    
    t.a=a1;
    t.b=a2;
    t.c=a3;
    
    current.x=0;
    current.y=0;
    
    nbr = rand() % 3 + 1;
    
    switch (nbr)
    {
        case 1:
            current=center(current,a1);
        break;
        case 2
            current=center(current,a2);
        break;
        case 3
            current=center(current,a3);
        break;
    }
    return 0;
}
