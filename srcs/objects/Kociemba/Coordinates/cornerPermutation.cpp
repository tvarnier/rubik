#include "../Kociemba.hpp"

unsigned int        Kociemba::Coord::cornerPermutation(const std::array<CORNERS, 8>& cornerPermutation)
{
    unsigned int fact = 1;
    unsigned int coord = 0;
    for (unsigned int i = 1; i < 8; ++i)
    {
        fact *= i;
        for (unsigned int y = 0; y < i; ++y)
            if (cornerPermutation[i] < cornerPermutation[y])
                coord += fact;
    }
    return (coord);
}

std::array<CORNERS, 8>  Kociemba::Coord::Generate::cornerPermutation(unsigned int coord)
{
    std::array<CORNERS, 8> tmp {URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB};

    unsigned int fact = 5040;
    for (unsigned int i = 7; i > 0; --i)
    {
        unsigned int greater = (coord % (fact * (i + 1))) / fact;
        CORNERS     t = tmp[i - greater];
        while (greater)
        {
            tmp[i - greater] = tmp[i - greater + 1];
            --greater;
        }
        tmp[i] = t;
        fact /= i;
    }

    return (tmp);
}
