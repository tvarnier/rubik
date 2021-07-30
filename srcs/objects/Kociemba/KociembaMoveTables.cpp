# include "Kociemba.hpp"

/* ===================== P2 ===================== */

void    Kociemba::generate_CornerOrientation_MoveTable()
{
    for (int i = 0; i < CORNER_ORIENTATION_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < P1_NBR_MOVE; ++y)
            CornerOrientation_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < CORNER_ORIENTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<unsigned int, 8> cornOrient = generateCornerOrientation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<unsigned int, 8>  cornOrientRotated = cornOrient;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                cornOrientRotated = Cube::rotateCornOrient(cornOrientRotated, rotateId);
                CornerOrientation_MoveTable[raw][moveId] = cornerOrientationCoordinates(cornOrientRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::generate_EdgeOrientation_MoveTable()
{
    for (int i = 0; i < EDGE_ORIENTATION_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < P1_NBR_MOVE; ++y)
            EdgeOrientation_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < EDGE_ORIENTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<unsigned int, 12> edgeOrient = generateEdgeOrientation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<unsigned int, 12>  edgeOrientRotated = edgeOrient;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgeOrientRotated = Cube::rotateEdgeOrient(edgeOrientRotated, rotateId);
                EdgeOrientation_MoveTable[raw][moveId] = edgeOrientationCoordinates(edgeOrientRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::generate_UdSlice_MoveTable()
{
    for (int i = 0; i < UD_SLICE_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < P1_NBR_MOVE; ++y)
            UdSlice_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < UD_SLICE_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateUDSlice(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12>  edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                UdSlice_MoveTable[raw][moveId] = UDSliceCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }
}

/* ===================== P2 ===================== */

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
}

int     Kociemba::generate_moveTables()
{
    generate_CornerOrientation_MoveTable();
    generate_EdgeOrientation_MoveTable();
    generate_UdSlice_MoveTable();
    generate_CornerPermutation_MoveTable();
    generate_P2EdgePermutation_MoveTable();
    generate_UdSliceSorted_MoveTable();

    return (0);
}