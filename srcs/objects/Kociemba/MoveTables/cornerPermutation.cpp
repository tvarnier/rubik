#include "../Kociemba.hpp"

void    Kociemba::MoveTable::Generate::CornerPermutation()
{
    for (int i = 0; i < CORNER_PERMUTATION_MOVETABLE_SIZE; ++i)
        for (int y = 0; y < 18; ++y)
            MoveTable::CornerPermutation[i][y] = 0;
    
    for (unsigned int raw = 0; raw < CORNER_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<CORNERS, 8> cornPerm = Coord::Generate::cornerPermutation(raw);

        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<CORNERS, 8>  cornPermRotated = cornPerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                cornPermRotated = Cube::rotateCornPerm(cornPermRotated, rotateId);
                MoveTable::CornerPermutation[raw][moveId] = Coord::cornerPermutation(cornPermRotated);
                ++moveId;
            }
        }
    }
}