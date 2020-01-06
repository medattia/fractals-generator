// demonstrates the usage of intelligent pointers

#include <iostream>
#include <memory>

using namespace std;
 
   
class Test
{
    public:
        Test(int a=0) : m_a(a) {};
        ~Test()
        {
            cout<< "Calling destructor" <<endl;    
        }
        
        int m_a;
};

void fun(shared_ptr <Test> p1)
{
    cout<<"Now we change the ownership of the object from pointer p to pointer p1"<<endl;
    cout<<"The value of the object member is : "<<p1->m_a<<endl;
    cout<< "The number of instances sharing this ressource is "<<p1.use_count() <<endl;      
}
int main ()
{
    shared_ptr <string> ptr(new string("Hello")); // auto_ptr has been deprecated
    cout<< *ptr <<endl;    
    cout<< ptr->at(1) <<endl;  
    *ptr+=" People of planet earth";
    cout<< *ptr <<endl;  
    // the reason why auto_ptr is obsolete now
    shared_ptr <Test> p(new Test(5));
    fun(p);
    cout<< p->m_a <<endl;    
    cout<< "The number of instances sharing this ressource is "<<p.use_count() <<endl;      
    shared_ptr<Test> sptr(new Test[5], [] (Test *p) {delete[] p;});  //declare array 
    return 0;
}
