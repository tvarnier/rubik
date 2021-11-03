#include "../Kociemba.hpp"

void    Kociemba::MoveTable::Generate::CornerOrientation()
{
    for (int i = 0; i < CORNER_ORIENTATION_MOVETABLE_SIZE; ++i)
        for (int y = 0; y < P1_NBR_MOVE; ++y)
            MoveTable::CornerOrientation[i][y] = 0;

    for (unsigned int raw = 0; raw < CORNER_ORIENTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<unsigned int, 8> cornOrient = Coord::Generate::cornerOrientation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<unsigned int, 8>  cornOrientRotated = cornOrient;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                cornOrientRotated = Cube::rotateCornOrient(cornOrientRotated, rotateId);
                MoveTable::CornerOrientation[raw][moveId] = Coord::cornerOrientation(cornOrientRotated);
                ++moveId;
            }
        }
    }
}