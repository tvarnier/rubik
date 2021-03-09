#include "lib.hpp"

double  lib::floor(double value)
{
    double tmp = (double) (int) value;
    return (tmp != value) ? (tmp - 1.0) : tmp;
}