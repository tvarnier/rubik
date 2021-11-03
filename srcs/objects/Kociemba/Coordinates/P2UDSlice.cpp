#include "../Kociemba.hpp"

unsigned int        Kociemba::Coord::P2UDSlice(const std::array<EDGES, 12>& edgePermutation)
{
    unsigned int    coord(0);
    unsigned int    nbr_slice(3);

    for (int i = 11; i >= 0 && nbr_slice; --i)
    {
        if (edgePermutation[i] >= FR)
        {
            unsigned int s(0);
            for (int y = i - 1; y >= 0; --y)
            {
                if (edgePermutation[y] >= FR && edgePermutation[y] > edgePermutation[i])
                    ++s;
            }
            coord = (coord + s) * nbr_slice;
            --nbr_slice;
        }
    }

    return (coord);
}

std::array<EDGES, 12>  Kociemba::Coord::Generate::P2UDSlice(unsigned int coord)
{
    std::array<EDGES, 12> tmp {UR,UF,UL,UB,DR,DF,DL,DB,FR,FL,BL,BR};

    unsigned int    nbr_slice(3);
    unsigned int    fact(6);

    for (unsigned int i = 11; i > 8; --i)
    {
        unsigned int    greater = coord / fact;
        EDGES           t = tmp[i - greater];
        while (greater)
        {
            tmp[i - greater] = tmp[i - greater + 1];
            --greater;
        }
        tmp[i] = t;
        coord %= fact;
        fact /= nbr_slice;
        nbr_slice--;
    }

    return (tmp);
}