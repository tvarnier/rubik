#include "Kociemba.hpp"

void    Kociemba::generate_symCubes()
{
    Cube sym;
    Cube tmpF2 = sym;
    for (int f2 = 0; f2 < 2; ++f2)
    {
        if (f2)
            tmpF2.rotation(ROT_F2);
        Cube tmpU4 = tmpF2;
        for (int u4 = 0; u4 < 4; ++u4)
        {
            if (u4)
                tmpU4.rotation(ROT_U4);
            Cube tmpLR2 = tmpU4;
            for (int lr2 = 0; lr2 < 2; ++lr2)
            {
                if (lr2)
                    tmpLR2.rotation(ROT_LR2);
                symCubes[f2 * 8 + u4 * 2 + lr2] = tmpLR2;
            }
        }
    }
}

void    Kociemba::generate_symInvCubes()
{
    for (int i = 0; i < 16; ++i)
        for (int y = 0; y < 16; ++y)
            {
                Cube tmp = Cube::multCube(symCubes[i], symCubes[y]);
                if (tmp.m_corners.p[URF] == URF && tmp.m_corners.p[UFL] == UFL && tmp.m_corners.p[ULB] == ULB)
                {
                    symInvCubes[i] = symCubes[y];
                    break ;
                }
            }
}

void    Kociemba::generate_symmetries()
{
    generate_symCubes();
    generate_symInvCubes();
}

unsigned int    Kociemba::getCornPermSymRep(const std::array<CORNERS, 8> cornPerm)
{
    unsigned int    rep(2147483647);

    for (int i = 0; i < 16; ++i)
    {
        std::array< CORNERS, 8 >    tmp;
        tmp = Cube::multCornPerm( Cube::multCornPerm(symInvCubes[i].m_corners.p, cornPerm), symCubes[i].m_corners.p );
        unsigned int coord = cornerPermutationCoordinates(tmp);
        rep = (coord < rep) ? coord : rep;
    }
    return (rep);
}