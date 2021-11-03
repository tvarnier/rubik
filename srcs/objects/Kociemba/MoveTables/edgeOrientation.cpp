#include "../Kociemba.hpp"

void    Kociemba::MoveTable::Generate::EdgeOrientation()
{
    for (int i = 0; i < EDGE_ORIENTATION_MOVETABLE_SIZE; ++i)
        for (int y = 0; y < P1_NBR_MOVE; ++y)
            MoveTable::EdgeOrientation[i][y] = 0;

    for (unsigned int raw = 0; raw < EDGE_ORIENTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<unsigned int, 12> edgeOrient = Coord::Generate::edgeOrientation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<unsigned int, 12>  edgeOrientRotated = edgeOrient;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgeOrientRotated = Cube::rotateEdgeOrient(edgeOrientRotated, rotateId);
                MoveTable::EdgeOrientation[raw][moveId] = Coord::edgeOrientation(edgeOrientRotated);
                ++moveId;
            }
        }
    }
}