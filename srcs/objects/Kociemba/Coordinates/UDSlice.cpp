#include "../Kociemba.hpp"

static int          binomialCoeff(int n, int k)
{
    int res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

unsigned int        Kociemba::Coord::UDSlice(const std::array<EDGES, 12>& edgePermutation)
{
    int             coord(0);
    int             coeff(-1);

    for (unsigned int i = 0; i < 12; ++i)
    {
        if (edgePermutation[i] >= FR)
            coeff += 1;
        else if (coeff >= 0)
        {
            coord += binomialCoeff((int)i , coeff);
        }
    }

    return ((unsigned int)coord);
}

std::array<EDGES, 12>   Kociemba::Coord::Generate::UDSlice(unsigned int coord)
{
    std::array<EDGES, 12> tmp {UR,UF,UL,UB,DR,DF,DL,DB,FR,FL,BL,BR};
    int coeff((( coord >= binomialCoeff(11 , 3)) ? 3 : 2));
    int tmpCoord(coord);

    unsigned int edge = (unsigned int)7;
    unsigned int sliceEdge = (unsigned int)11 - (3 - coeff);

    for (int i = 11 - (3 - coeff); i >= 0 && coeff >= 0; --i)
    {
        unsigned int bc = binomialCoeff((int)i , coeff);
        if (tmpCoord >= bc)
        {
            tmpCoord -= bc;
            tmp[i] = (EDGES)edge;
            --edge;
        }
        else
        {
            --coeff;
            tmp[i] = (EDGES)sliceEdge;
            --sliceEdge;
        }
    }

    return tmp;
}