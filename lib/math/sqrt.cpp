#include "lib.hpp"

double      lib::sqrt(double x)
{
    int     exp{0};

    if (x <= 0)
        return (0);
    x = lib::frexp(x, exp);
    if (exp & 1)
    {
        --exp;
        x *= 2;
    }
    double y = (1 + x) / 2;
    double z = 0;
    while (y != z)
    {
        z = y;
        y = (y + x / y) / 2;
    }
    return lib::ldexp(y, exp / 2);
}