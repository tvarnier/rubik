#include "../Kociemba.hpp"

void    Kociemba::Sym::Rep::Generate::cornerPermutation()
{
    int repId(0);
    for (unsigned int raw = 0; raw < CORNER_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<CORNERS, 8> cornPerm = Coord::Generate::cornerPermutation(raw);
        unsigned int    rep(2147483647);

        int i(0);
        for (i = 0; i < 16; ++i)
        {
            std::array< CORNERS, 8 >    tmp;
            tmp = Cube::multCornPerm( Cube::multCornPerm(Sym::invCubes[i].m_corners.p, cornPerm), Sym::Cubes[i].m_corners.p );
            unsigned int coord = Coord::cornerPermutation(tmp);
            
            if (coord < raw)
                    break ;
        }
        if (i == 16)
            Sym::Rep::cornerPermutation[repId++] = raw;
    }
}

void    Kociemba::Sym::RepTable::Generate::generate_CornerPermutationSym_MoveTable()
{
    Rep::Generate::cornerPermutation();

    int repId(0);
    for (unsigned int raw = 0; raw < CORNER_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<CORNERS, 8> cornPerm = Coord::Generate::cornerPermutation(raw);

        if (Sym::Rep::cornerPermutation[repId] == raw)
        {
            for (int i = 0; i < 16; ++i)
            {
                std::array< CORNERS, 8 >    tmp;
                tmp = Cube::multCornPerm( Cube::multCornPerm(Sym::Cubes[i].m_corners.p, cornPerm), Sym::invCubes[i].m_corners.p );
                unsigned int coord = Coord::cornerPermutation(tmp);
                
                Sym::RepTable::cornerPermutation[coord].first = repId;
                Sym::RepTable::cornerPermutation[coord].second.push_back(i);
            }
            ++repId;
        }
    }
}