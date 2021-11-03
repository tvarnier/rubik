#include "../Kociemba.hpp"

unsigned int        Kociemba::Coord::P2EdgePermutation(const std::array<EDGES, 12>& edgePermutation)
{
    unsigned int fact = 1;
    unsigned int coord = 0;
    for (unsigned int i = 1; i < 8; ++i)
    {
        fact *= i;
        for (unsigned int y = 0; y < i; ++y)
            if (edgePermutation[i] < edgePermutation[y])
                coord += fact;
    }
    return (coord);
}

std::array<EDGES, 12>  Kociemba::Coord::Generate::P2EdgePermutation(unsigned int coord)
{
    std::array<EDGES, 12> tmp {UR,UF,UL,UB,DR,DF,DL,DB,FR,FL,BL,BR};

    unsigned int fact = 5040;
    for (unsigned int i = 7; i > 0; --i)
    {
        unsigned int    greater = (coord % (fact * (i + 1))) / fact;
        EDGES           t = tmp[i - greater];
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