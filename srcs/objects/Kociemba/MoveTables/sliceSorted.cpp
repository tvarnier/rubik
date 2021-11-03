#include "../Kociemba.hpp"

void    Kociemba::MoveTable::Generate::UDSliceSorted()
{
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
        for (int y = 0; y < 18; ++y)
            MoveTable::UDSliceSorted[i][y] = 0;

    for (unsigned int raw = 0; raw < UD_SLICE_SORTED_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = Coord::Generate::UDSliceSorted(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                MoveTable::UDSliceSorted[raw][moveId] = Coord::UDSliceSorted(edgePermRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::MoveTable::Generate::FBSliceSorted()
{
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
        for (int y = 0; y < 18; ++y)
            MoveTable::FBSliceSorted[i][y] = 0;

    for (unsigned int raw = 0; raw < UD_SLICE_SORTED_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = Coord::Generate::FBSliceSorted(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                MoveTable::FBSliceSorted[raw][moveId] = Coord::FBSliceSorted(edgePermRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::MoveTable::Generate::RLSliceSorted()
{
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < 18; ++y)
            MoveTable::RLSliceSorted[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < UD_SLICE_SORTED_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = Coord::Generate::RLSliceSorted(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                MoveTable::RLSliceSorted[raw][moveId] = Coord::RLSliceSorted(edgePermRotated);
                ++moveId;
            }
        }
    }
}