#include <functional>
#include <iostream>
#include <vector>
using namespace std;
double eval(function<double(double)> f, double x = 2.0) {
  return f(x);
}

int main() {
  function<double(double)> f0 = [](double x) { return 1; };
  auto f1 = [](double x) { return x; };
  decltype(f0) fa[3] = {f0, f1, [](double x) { return x * x; }};
  vector<decltype(f0)> fv = {f0, f1};
  fv.push_back([](double x) { return x * x; });
  for (size_t i = 0; i < fv.size(); i++) {
    cout << fv[i](2.0) << std::endl;
  }
  for (size_t i = 0; i < 3; i++) {
    cout << fa[i](2.0) << endl;
  }
  for (auto& f : fv) {
    cout << f(2.0) << endl;
  }
  for (auto& f : fa) {
    cout << f(2.0) << endl;
  }
  std::cout << eval(f0) << std::endl;
  std::cout << eval(f1) << std::endl;
  std::cout << eval([](double x) { return x * x; }) << std::endl;
}

//A lambda expression with an empty capture specification ([]) can be implicitly converted into a function pointer with the same type as the lambda was declared with. So this is legal:

//auto a_lambda_func = [](int x) { /*...*/ };
//void (* func_ptr)(int) = a_lambda_func;
//func_ptr(4); //calls the lambda.

