#include "../Kociemba.hpp"

unsigned int        Kociemba::Coord::edgeOrientation(const std::array<unsigned int, 12>& edgeOrientation)
{
    unsigned int modulo = 1024;

    unsigned int coord = 0;
    
    for ( unsigned int i = 0; i < 11; ++i)
    {
        coord += edgeOrientation[i] * modulo;
        modulo /= 2;
    }
    return (coord);
}

std::array<unsigned int, 12> Kociemba::Coord::Generate::edgeOrientation(unsigned int coord)
{
    std::array<unsigned int, 12> tmp = {};

    unsigned int modulo = 1;
    unsigned int total = 0;

    for (int i = 10; i >= 0; --i)
    {
        tmp[i] = (coord / modulo) % 2;
        total += tmp[i];
        modulo *= 2;
    }
    if (total % 2)
        tmp[11] = 2 - (total % 2);
    return (tmp);
}