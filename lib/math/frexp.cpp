#include "lib.hpp"

double   lib::frexp(double x, int &exp)
{
    double  tmp{0};

    while ((tmp = x / lib::pow((double)2, (double)exp)) >= 1)
        ++exp;
    return (x / lib::pow(2, exp));
}