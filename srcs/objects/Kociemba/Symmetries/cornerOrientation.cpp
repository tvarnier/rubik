#include "../Kociemba.hpp"

void    Kociemba::Sym::MoveTable::Generate::cornerOrientation()
{
    for (unsigned int raw = 0; raw < 2187; ++raw)
    {
        struct corners corner;
        corner.o = Coord::Generate::cornerOrientation(raw);
        for (int sym = 0; sym < 16; ++sym)
            Sym::MoveTable::cornerOrientation[raw][sym] = Coord::cornerOrientation(Cube::multCorners( Cube::multCorners(Sym::invCubes[sym].m_corners, corner), Sym::Cubes[sym].m_corners ).o);
    }
}