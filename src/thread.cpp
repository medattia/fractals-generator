 #include <iostream>
#include <cstdlib>
    #include <thread>
    #include <vector>
    #include <future>

            #include <functional>
using namespace std;

     vector<double> some_vec{4,5,6,7};
     
        void f(vector<double>&, double* res);   // place result in res
        struct F {
            vector<double>& v;
            double* res;
            F(vector<double>& vv, double* p) :v{vv}, res{p} { }
            void operator()();  // place result in res
        };
        int main()
        {
            double res1;
            double res2;
            std::thread t1{std::bind(f,some_vec,&res1)};    // f(some_vec,&res1) executes in separate thread
            std::thread t2{F(some_vec,&res2)};      // F(some_vec,&res2)() executes in separate thread
            t1.join();
            t2.join();
            std::cout << res1 << ' ' << res2 << '\n';
        }
