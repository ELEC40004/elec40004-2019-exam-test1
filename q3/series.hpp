#ifndef series_hpp
#define series_hpp

#include <utility>
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#include "function.hpp"

/* Describes a series a0 + a1 x + a2 x^2 + ...
*/
class Series
    : public Function
{
public:
    //! Return the coefficient of x^p
    /* Non-const as it may be necessary to update state to calculate a particular coefficient efficiently. */
    virtual double a(int p) =0;

    //! Evaluate the function at position x using terms a0 ... a{n-1}
    /* Non-const because a is non-const. */
    virtual double evaluate_truncated(double x, int n)
    {
        double acc=0;
        for(int i=0; i<n; i++){
            acc += a(i) * pow(x, i);
        }
        return acc;
    }

    //! Evaluate the function at position x, adding more terms until tolerance is met
    /* Non-const because a and evaluate_truncated are non-const. */
    virtual double evaluate_to_tolerance(double x, double tol, int max_n)
    {
        // TODO: Implement

        cerr<<"Exceeded maximum iterations "<<max_n<<" without reaching tolerance "<<tol<<endl;
        exit(1);
    }

    //! Default evaluation, with a tolerance 10^-9, and a maximum of 10000 coefficients
    double evaluate(double x) override
    {
        return evaluate_to_tolerance(x, 1e-9, 10000);
    }

    //! Return true if this series only has a constant term
    /*! implies that a_1,a_2,a_3,... are all zero. */
    virtual bool is_constant() const
    { return false; }

    //! Return true if this series consists of just x
    /*! implies that a_1=1, and a_0, a_2,a_3,... are all zero. */
    virtual bool is_variable() const
    { return false; }
};

Series *series_factory(const string &name, const vector<Series*> &args);

#endif
