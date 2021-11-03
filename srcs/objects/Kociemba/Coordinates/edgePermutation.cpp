#include "../Kociemba.hpp"

unsigned int        Kociemba::Coord::edgePermutation(const std::array<EDGES, 12>& edgePermutation)
{
    unsigned int fact = 1;
    unsigned int coord = 0;
    for (unsigned int i = 1; i < 12; ++i)
    {
        fact *= i;
        for (unsigned int y = 0; y < i; ++y)
            if (edgePermutation[i] < edgePermutation[y])
                coord += fact;
    }
    return (coord);
}