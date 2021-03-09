#include "lib.hpp"
#include <cmath>

double      lib::pgcd(double a, double b)
{
    if (a < b)
        swap(a, b);
    if (lib::fabs(a - b) < 0.0001)
        return (a);
    else
        return (lib::pgcd(b, a - b));
}