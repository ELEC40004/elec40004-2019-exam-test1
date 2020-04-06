#include "series_operations.hpp"

class SeriesDerivative
    : public Series
{
private:
    Series *m_a;
public:
    SeriesDerivative(Series *a)
        : m_a(a)
    {
    }

    ~SeriesDerivative() override
    {
        delete m_a;
    }

    virtual double a(int p) override
    {
        return m_a->a(p+1) * (p+1);
    }
};

Series *series_derivative(Series *s)
{
    return new SeriesDerivative(s);
}