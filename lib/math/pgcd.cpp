#include "lib.hpp"
#include <cmath>

#include <math.h>

#include <numeric>

double      lib::pgcd(double a, double b)
{
    if (a < b)
        swap(a, b);

    while (a > b && b >= 0.0001)
    {
        double tmp = a;
        a = b;
        b = tmp - lib::floor(tmp / a) * a;
    }
    return (a);
}