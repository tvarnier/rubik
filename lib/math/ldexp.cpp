#include "lib.hpp"

double      lib::ldexp(double x, int exp)
{
    return (x * lib::pow((double)2, (double)exp));
}