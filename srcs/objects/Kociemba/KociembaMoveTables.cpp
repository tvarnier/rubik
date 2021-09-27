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

    Kociemba::CornOrientSym_MoveTable.resize(2187);

    for (unsigned int raw = 0; raw < 2187; ++raw)
    {
        struct corners corner;
        corner.o = generateCornerOrientation(raw);
        for (int sym = 0; sym < 16; ++sym)
            Kociemba::CornOrientSym_MoveTable[raw][sym] = cornerOrientationCoordinates(Cube::multCorners( Cube::multCorners(symInvCubes[sym].m_corners, corner), symCubes[sym].m_corners ).o);
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

void    Kociemba::generate_FlipUdSlice_MoveTable()
{
    lib::printendl("HEY");
    FlipUdSlice_MoveTable.resize(1013760);
    lib::printendl("HEY");

    std::array<unsigned int, 16> tmpSyms {};
    int repId(-1);

    FlipUdSlice_Sym.resize(FLIP_UD_SLICE_MOVETABLE_SIZE);

    for (unsigned int raw = 0; raw < FLIP_UD_SLICE_MOVETABLE_SIZE; ++raw)
    {
        struct edges Coord;
        Coord.o = generateEdgeOrientation(raw / UD_SLICE_MOVETABLE_SIZE);
        Coord.p = generateUDSlice(raw % UD_SLICE_MOVETABLE_SIZE);

        int i(0);
        for (i = 0; i < 16; ++i)
        {
            struct edges tmpCoord = Coord;

            tmpCoord = Cube::multEdges(Cube::multEdges(symCubes[i].m_edges, tmpCoord), symInvCubes[i].m_edges);

            unsigned int coord = edgeOrientationCoordinates(tmpCoord.o) * UD_SLICE_MOVETABLE_SIZE + UDSliceCoordinates(tmpCoord.p);
            
            if (coord < raw)
                break ;
            
            tmpSyms[i] = coord;
        }

        if (i == 16)
        {
            FlipUdSlice_SymRep[++repId] = raw;
            for (int sym = 0; sym < 16; ++sym)
            {
                FlipUdSlice_Sym[tmpSyms[sym]].first = repId;
                FlipUdSlice_Sym[tmpSyms[sym]].second.push_back(sym);
            }
        }

        unsigned int edgeOrientation = raw / UD_SLICE_MOVETABLE_SIZE;
        unsigned int udSlice = raw % UD_SLICE_MOVETABLE_SIZE;

        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            struct edges tmpCoord = Coord;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                tmpCoord = Cube::rotateEdges(tmpCoord, rotateId);
                FlipUdSlice_MoveTable[raw][moveId] = edgeOrientationCoordinates(tmpCoord.o) * UD_SLICE_MOVETABLE_SIZE + UDSliceCoordinates(tmpCoord.p);
                ++moveId;
            }
        }
    }

    lib::printendl("HEY");
}

/* ===================== P2 ===================== */

void    Kociemba::generate_CornerPermutation_MoveTable()
{
    for (int i = 0; i < CORNER_PERMUTATION_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < 18; ++y)
            CornerPermutation_MoveTable[i][y] = 0;
    }

    int repId(-1);

    for (unsigned int raw = 0; raw < CORNER_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<CORNERS, 8> cornPerm = generateCornerPermutation(raw);

        if (getCornPermSymRep(cornPerm) == raw)
        {
            CornPerm_SymRep[++repId] = raw;
            printf(" %5d : [ ", raw);
            for (int i = 0; i < 16; ++i)
            {

                std::array< CORNERS, 8 >    tmp;
                tmp = Cube::multCornPerm( Cube::multCornPerm(symCubes[i].m_corners.p, cornPerm), symInvCubes[i].m_corners.p );
                unsigned int coord = cornerPermutationCoordinates(tmp);
                
                printf(" %5d ", coord);
                CornPerm_Sym[coord].first = repId;
                CornPerm_Sym[coord].second.push_back(i);
            }
            printf("]\n");
        }

        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<CORNERS, 8>  cornPermRotated = cornPerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                cornPermRotated = Cube::rotateCornPerm(cornPermRotated, rotateId);
                CornerPermutation_MoveTable[raw][moveId] = cornerPermutationCoordinates(cornPermRotated);
                ++moveId;
            }
        }
    }

    std::printf("nbRepId : %d\n", repId);



    /*for (unsigned int sym = 0; sym < 2768; ++sym)
    {
        unsigned int raw = CornSymRep[sym];
        std::array<CORNERS, 8> cornPerm = generateCornerPermutation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<CORNERS, 8>  cornPermRotated = cornPerm;
            // unsigned int maxRotation = (rotateId == UP || rotateId == DOWN) ? 3 : 1;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                cornPermRotated = Cube::rotateCornPerm(cornPermRotated, rotateId);
                CornPermSym_MoveTable[sym][moveId] = cornerPermutationCoordinates(cornPermRotated);
                if (sym == 0) lib::printendl(":: ", CornPermSym_MoveTable[sym][moveId] );
                ++moveId;
            }
        }

    }*/
}

void    Kociemba::generate_P2EdgePermutation_MoveTable()
{
    for (int i = 0; i < P2_EDGE_PERMUTATION_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < 18; ++y)
            P2EdgePermutation_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < P2_EDGE_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateP2EdgePermutation(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            // unsigned int maxRotation = (rotateId == UP || rotateId == DOWN) ? 3 : 1;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                // if (rotateId != UP && rotateId != DOWN)
                //     edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                P2EdgePermutation_MoveTable[raw][moveId] = phase2EdgePermutationCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }

    Kociemba::P2EdgePermSym_MoveTable.resize(40320);

    for (unsigned int raw = 0; raw < 40320; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateP2EdgePermutation(raw);
        for (int sym = 0; sym < 16; ++sym)
            Kociemba::P2EdgePermSym_MoveTable[raw][sym] = phase2EdgePermutationCoordinates(Cube::multEdgePerm( Cube::multEdgePerm(symInvCubes[sym].m_edges.p, edgePerm), symCubes[sym].m_edges.p ));
    }
}

void    Kociemba::generate_UdSliceSorted_MoveTable()
{
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < 18; ++y)
            UdSliceSorted_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < UD_SLICE_SORTED_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateUDSliceSorted(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            // unsigned int maxRotation = (rotateId == UP || rotateId == DOWN) ? 3 : 1;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                // if (rotateId != UP && rotateId != DOWN)
                //     edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
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
    generate_FlipUdSlice_MoveTable();

    generate_CornerPermutation_MoveTable();
    generate_P2EdgePermutation_MoveTable();
    generate_UdSliceSorted_MoveTable();

    return (0);
}