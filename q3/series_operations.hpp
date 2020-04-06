#ifndef series_operations_hpp
#define series_operations_hpp

#include "series.hpp"

/* Operations which return a new transformed series will take
   ownership of the base series - the caller should delete
   the returned object instead.
*/

//! Create a cache over the coefficients so that they are only ever calculated once.
Series *series_cache(Series *base);

//! Returns the derivative of the series
Series *series_derivative(Series *base);

//! Returns the integral of the series
Series *series_integral(Series *base);

//! Returns the sum of the series
Series *series_sum(Series *a, Series *b);

//! Returns the product of the series
Series *series_product(Series *a, Series *b);


//! Returns the constant c
Series *series_make_constant(double c);

//! Returns the variable x
Series *series_make_variable();

//! Returns the cos of base
/*! It is only required to handle the case where base is the variable x.*/
Series *series_cos(Series *base);

//! Returns the sin of base
/*! It is only required to handle the case where base is the variable x.*/
Series *series_sin(Series *base);


//! Reads a series from a string
Series *series_parse(const string &s);

//! Reads a series from the given stream
Series *series_parse(istream &s);



#endif
