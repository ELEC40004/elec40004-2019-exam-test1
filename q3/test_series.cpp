#include "series_operations.hpp"

void test_series(Series *s, Function *f, double a, double b, double delta, double eps)
{
    for(double x=a; x<=b; x+=delta){
        double got=s->evaluate_to_tolerance(x, eps/4, 10000);
        double ref=f->evaluate(x);

        if( abs(got-ref) >= eps ){
            cerr << "x="<<x<<", got="<<got<<", ref="<<ref<<endl;
            exit(1);
        }
    }
}

class SinFunction
    : public Function
{
public:
    double evaluate(double x) override
    { return sin(x);  }
};

int main()
{
    Series *s;
    Function *f;

    s=series_parse("( sin x )");
    f=new SinFunction();

    test_series(s, f, -1, 1, 0.1, 1e-5);

    delete s;
    delete f;
}