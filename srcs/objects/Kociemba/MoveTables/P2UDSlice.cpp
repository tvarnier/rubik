#include "../Kociemba.hpp"

void    Kociemba::MoveTable::Generate::P2UDSlice()
{
    for (int i = 0; i < P2_UD_SLICE_MOVETABLE_SIZE; ++i)
        for (int y = 0; y < 18; ++y)
            MoveTable::P2UDSlice[i][y] = 0;

    for (unsigned int raw = 0; raw < P2_UD_SLICE_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = Coord::Generate::P2UDSlice(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                MoveTable::P2UDSlice[raw][moveId] = Coord::P2UDSlice(edgePermRotated);
                ++moveId;
            }
        }
    }
}