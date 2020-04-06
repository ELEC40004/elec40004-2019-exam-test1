#include "series_operations.hpp"

class SeriesVariable
    : public Series
{
public:
    SeriesVariable()
    {
    }

    virtual double a(int p) override
    {
        if(p==1){
            return 1;
        }else{
            return 0.0;
        }
    }

    virtual bool is_variable() const
    { return true; }
};

Series *series_make_variable()
{
    return new SeriesVariable();
}