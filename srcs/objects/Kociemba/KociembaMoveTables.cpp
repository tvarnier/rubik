# include "Kociemba.hpp"

void    Kociemba::generate_CornerPermutation_MoveTable()
{
    CornerPermutation_MoveTable.resize(CORNER_PERMUTATION_MOVETABLE_SIZE);

    for (int i = 0; i < CORNER_PERMUTATION_MOVETABLE_SIZE; ++i)
    {
        CornerPermutation_MoveTable[i].first.resize(10);
        CornerPermutation_MoveTable[i].second = 0;
        for (int y = 0; y < 10; ++y)
            CornerPermutation_MoveTable[i].first[y] = 0;
    }

    for (unsigned int raw = 0; raw < CORNER_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<CORNERS, 8> cornPerm = generateCornerPermutation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<CORNERS, 8>  cornPermRotated = cornPerm;
            unsigned int test = (rotateId == UP || rotateId == DOWN) ? 3 : 1;
            for (unsigned int nbrRotate = 0; nbrRotate < test ; ++nbrRotate)
            {
                cornPermRotated = Cube::rotateCornPerm(cornPermRotated, rotateId);
                if (rotateId != UP && rotateId != DOWN)
                    cornPermRotated = Cube::rotateCornPerm(cornPermRotated, rotateId);
                CornerPermutation_MoveTable[raw].first[moveId] = cornerPermutationCoordinates(cornPermRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::generate_P2EdgePermutation_MoveTable()
{
    P2EdgePermutation_MoveTable.resize(P2_EDGE_PERMUTATION_MOVETABLE_SIZE);

    for (int i = 0; i < P2_EDGE_PERMUTATION_MOVETABLE_SIZE; ++i)
    {
        P2EdgePermutation_MoveTable[i].first.resize(10);
        P2EdgePermutation_MoveTable[i].second = 0;
        for (int y = 0; y < 10; ++y)
            P2EdgePermutation_MoveTable[i].first[y] = 0;
    }

    for (unsigned int raw = 0; raw < P2_EDGE_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateP2EdgePermutation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12>  edgePermRotated = edgePerm;
            unsigned int test = (rotateId == UP || rotateId == DOWN) ? 3 : 1;
            for (unsigned int nbrRotate = 0; nbrRotate < test ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                if (rotateId != UP && rotateId != DOWN)
                    edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                P2EdgePermutation_MoveTable[raw].first[moveId] = phase2EdgePermutationCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }
}

int     Kociemba::generate_moveTables()
{
    generate_P2EdgePermutation_MoveTable();
    generate_CornerPermutation_MoveTable();

    return (0);
}