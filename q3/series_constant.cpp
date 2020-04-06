#include "series_operations.hpp"

class SeriesConstant
    : public Series
{
private:
    double m_c;
public:
    SeriesConstant(double c)
        : m_c(c)
    {
    }

    virtual double a(int p) override
    {
        if(p==0){
            return m_c;
        }else{
            return 0.0;
        }
    }

    virtual bool is_constant() const
    { return true; }
};

Series *series_make_constant(double c)
{
    return new SeriesConstant(c);
}