# include "Kociemba.hpp"

void    Kociemba::generate_CornerPermutation_MoveTable()
{
    for (int i = 0; i < CORNER_PERMUTATION_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < P2_NBR_MOVE; ++y)
            CornerPermutation_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < CORNER_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<CORNERS, 8> cornPerm = generateCornerPermutation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<CORNERS, 8>  cornPermRotated = cornPerm;
            unsigned int maxRotation = (rotateId == UP || rotateId == DOWN) ? 3 : 1;
            for (unsigned int nbrRotate = 0; nbrRotate < maxRotation ; ++nbrRotate)
            {
                cornPermRotated = Cube::rotateCornPerm(cornPermRotated, rotateId);
                if (rotateId != UP && rotateId != DOWN)
                    cornPermRotated = Cube::rotateCornPerm(cornPermRotated, rotateId);
                CornerPermutation_MoveTable[raw][moveId] = cornerPermutationCoordinates(cornPermRotated);
                ++moveId;
            }
        }
    }

    /*for (unsigned int i = 0; i < CORNER_PERMUTATION_MOVETABLE_SIZE; ++i)
    {
        std::printf("%05u [ ", i);
        for (unsigned int y = 0; y < P2_NBR_MOVE; ++y)
        {
            std::printf("%05u", CornerPermutation_MoveTable[i][y]);
            if (y != P2_NBR_MOVE - 1)
                std::printf(", ");
        }
        std::printf(" ]\n");
    }*/
}

void    Kociemba::generate_P2EdgePermutation_MoveTable()
{
    for (int i = 0; i < P2_EDGE_PERMUTATION_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < P2_NBR_MOVE; ++y)
            P2EdgePermutation_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < P2_EDGE_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateP2EdgePermutation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            unsigned int maxRotation = (rotateId == UP || rotateId == DOWN) ? 3 : 1;
            for (unsigned int nbrRotate = 0; nbrRotate < maxRotation ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                if (rotateId != UP && rotateId != DOWN)
                    edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                P2EdgePermutation_MoveTable[raw][moveId] = phase2EdgePermutationCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::generate_UdSliceSorted_MoveTable()
{
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < P2_NBR_MOVE; ++y)
            UdSliceSorted_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < UD_SLICE_SORTED_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateUDSliceSorted(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            unsigned int maxRotation = (rotateId == UP || rotateId == DOWN) ? 3 : 1;
            for (unsigned int nbrRotate = 0; nbrRotate < maxRotation ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                if (rotateId != UP && rotateId != DOWN)
                    edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                UdSliceSorted_MoveTable[raw][moveId] = UDSliceSortedCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }

    /*for (unsigned int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
    {
        std::printf("%05u [ ", i);
        for (unsigned int y = 0; y < P2_NBR_MOVE; ++y)
        {
            std::printf("%05u", UdSliceSorted_MoveTable[i][y]);
            if (y != P2_NBR_MOVE - 1)
                std::printf(", ");
        }
        std::printf(" ]\n");
    }*/
}

int     Kociemba::generate_moveTables()
{
    generate_CornerPermutation_MoveTable();
    generate_P2EdgePermutation_MoveTable();
    generate_UdSliceSorted_MoveTable();

    return (0);
}