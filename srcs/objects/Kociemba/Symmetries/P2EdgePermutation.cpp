#include "../Kociemba.hpp"

void    Kociemba::Sym::MoveTable::Generate::P2EdgePermutation()
{
    for (unsigned int raw = 0; raw < 40320; ++raw)
    {
        std::array<EDGES, 12> edgePerm = Coord::Generate::P2EdgePermutation(raw);
        for (int sym = 0; sym < 16; ++sym)
            Sym::MoveTable::P2EdgePermutation[raw][sym] = Coord::P2EdgePermutation(Cube::multEdgePerm( Cube::multEdgePerm(Sym::invCubes[sym].m_edges.p, edgePerm), Sym::Cubes[sym].m_edges.p ));
    }
}