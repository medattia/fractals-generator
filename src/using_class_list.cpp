// demonstrates the usage of vectors
#include <iostream>
#include <list>

using namespace std;

class AAA
{
    friend ostream &operator<<(ostream &,const AAA &);
    public:
        int x,y;
        float z;
        AAA();
        AAA(const AAA &);
        ~AAA(){};
        AAA& operator=(const AAA &rhs);
        int operator== (const AAA &rhs) const;
        int operator< (const AAA &rhs) const;
};

AAA::AAA()          // default constructor
{
    x=0;y=0;z=0.0;
}

AAA::AAA(const AAA &copyin)          // copy constructor to handle pass by value
{
    x=copyin.x; 
    y=copyin.y;
    z=copyin.z;
}

ostream &operator<<(ostream &output, const AAA &aaa)
{
    output << aaa.x << ' ' << aaa.y << ' ' <<  aaa.z << endl;
    return output;
}

AAA& AAA::operator=(const AAA &rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;
    return *this;
}


int AAA::operator== (const AAA &rhs) const
{
    if( this->x  != rhs.x) {return 0;};
    if( this->y  != rhs.y) {return 0;};
    if( this->z  != rhs.z) {return 0;};
    return 1;
}

int AAA::operator< (const AAA &rhs) const
{
    if( this->x  == rhs.x && this->y  == rhs.y && this->z  < rhs.z) {return 1;};
    if( this->x  == rhs.x && this->y  < rhs.y) {return 1;};
    if( this->x  < rhs.x) {return 1;};
    return 0;
}
int main ()
{
    list <AAA> L;               
    AAA Ablob;
    Ablob.x=7;  Ablob.y=2;  Ablob.z=3.1416;

    L.push_back(Ablob);
    Ablob.z=0.16;
    L.push_back(Ablob);
    
    list<AAA>::iterator i;
    
    for(i=L.begin(); i!=L.end(); ++i) 
    {
        cout << "Dereferenced value (*i).x is:" << (*i).x << endl;
        cout << "The iterator value *i is:" << *i << endl;
    };
    cout << "Sorted: " << endl;
    L.sort();
    for(i=L.begin(); i!=L.end(); ++i) 
    {
        cout << "Dereferenced value (*i).x is:" << (*i).x << endl;
        cout << "The iterator value *i is:" << *i << endl;
    };
    return 0;
}
