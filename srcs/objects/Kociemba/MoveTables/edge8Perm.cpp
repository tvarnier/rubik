#include "../Kociemba.hpp"

void    Kociemba::MoveTable::Generate::Edge8Perm()
{
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
        for (int y = 0; y < 24; ++y)
            MoveTable::edge8Perm[i][y] = 0;

    for (unsigned int raw = 0; raw < P2_EDGE_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = Coord::Generate::P2EdgePermutation(raw);
        unsigned int RLSliceSortedCoord = Coord::RLSliceSorted(edgePerm);
        unsigned int FBSliceSortedCoord = Coord::FBSliceSorted(edgePerm);
        MoveTable::edge8Perm[RLSliceSortedCoord][FBSliceSortedCoord % 24] = raw;
    }
}