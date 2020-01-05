// demonstrates the usage of decltype (type deduction)
#include <iostream>

using namespace std;

template<class T>
T max(T array[], int length)
{
    T vmax = array[0];
    for (int i=0; i<length; i++) {if(array[i]> vmax) {vmax=array[i];};};
    return vmax;
}

int main ()
{
    int values[]={100, 5, 35, 7};
    cout << max(values,4) << endl;
    string noms[]={"Jupiter", "Mars", "Venus", "Pluton", "Uranus", "Mercure"};
    cout << max(noms,6) << endl;
    return 0;
}
