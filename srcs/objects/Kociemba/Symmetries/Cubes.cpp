#include "../Kociemba.hpp"

void    Kociemba::Sym::Generate::Cubes()
{
    Cube sym;
    Cube tmpURF3 = sym;
    for (int urf3 = 0; urf3 < 3; ++urf3)
    {
        if (urf3)
            tmpURF3.rotation(ROT_URF3);
        Cube tmpF2 = tmpURF3;
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
                    Sym::Cubes[urf3 * 16 + f2 * 8 + u4 * 2 + lr2] = tmpLR2;
                }
            }
        }
    }
}

void    Kociemba::Sym::Generate::invCubes()
{
    for (int i = 0; i < 48; ++i)
        for (int y = 0; y < 48; ++y)
            {
                Cube tmp = Cube::multCube(Sym::Cubes[i], Sym::Cubes[y]);
                if (tmp.m_corners.p[URF] == URF && tmp.m_corners.p[UFL] == UFL && tmp.m_corners.p[ULB] == ULB)
                {
                    Sym::invCubes[i] = Sym::Cubes[y];
                    break ;
                }
            }
}