#include "../Kociemba.hpp"

void    Kociemba::MoveTable::Generate::FlipUDSlice()
{
    for (unsigned int raw = 0; raw < FLIP_UD_SLICE_MOVETABLE_SIZE; ++raw)
    {
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                MoveTable::FlipUDSlice[raw][moveId] = MoveTable::EdgeOrientation[raw / UD_SLICE_MOVETABLE_SIZE][moveId] * UD_SLICE_MOVETABLE_SIZE + MoveTable::UDSlice[raw % UD_SLICE_MOVETABLE_SIZE][moveId];//;
                ++moveId;
            }
        }
    }
}