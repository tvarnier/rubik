#include "../Kociemba.hpp"

unsigned int        Kociemba::Coord::cornerOrientation(const std::array<unsigned int, 8>& cornerOrientation)
{
    unsigned int modulo = 729;

    unsigned int coord = 0;
    
    for ( unsigned int i = 0; i < 7; ++i)
    {
        coord += cornerOrientation[i] * modulo;
        modulo /= 3;
    }
    return (coord);
}

std::array<unsigned int, 8> Kociemba::Coord::Generate::cornerOrientation(unsigned int coord)
{
    std::array<unsigned int, 8> tmp = {};

    unsigned int modulo = 1;

    unsigned int total = 0;

    for (int i = 6; i >= 0; --i)
    {
        tmp[i] = (coord / modulo) % 3;
        total += tmp[i];
        modulo *= 3;
    }
    if (total % 3)
        tmp[7] = 3 - (total % 3);

    return (tmp);
}