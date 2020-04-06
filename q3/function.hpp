#ifndef function_hpp
#define function_hpp

#include <utility>
#include <cmath>

using namespace std;

class Function
{
public:
    virtual ~Function()
    {}

    // Evaluates the function at x
    virtual double evaluate(double x) =0;
};

#endif