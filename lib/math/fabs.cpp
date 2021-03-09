#include "lib.hpp"

double  lib::fabs(double nbr)
{
    return ((nbr >= 0.0) ? nbr : -nbr);
}