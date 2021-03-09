#include "lib.hpp"

double      lib::pow(double base, double exponent)
{
    double res{1};

    while (exponent)
    {
        res *= base;
        --exponent;
    }
    return (res);
}