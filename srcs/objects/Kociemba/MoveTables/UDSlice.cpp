#include "../Kociemba.hpp"

void    Kociemba::MoveTable::Generate::UDSlice()
{
    for (int i = 0; i < UD_SLICE_MOVETABLE_SIZE; ++i)
        for (int y = 0; y < P1_NBR_MOVE; ++y)
            MoveTable::UDSlice[i][y] = 0;

    for (unsigned int raw = 0; raw < UD_SLICE_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = Coord::Generate::UDSlice(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12>  edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                MoveTable::UDSlice[raw][moveId] = Coord::UDSlice(edgePermRotated);
                ++moveId;
            }
        }
    }
}