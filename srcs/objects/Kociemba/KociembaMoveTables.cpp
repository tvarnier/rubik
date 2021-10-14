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

void    Kociemba::generate_UDSlice_MoveTable()
{
    for (int i = 0; i < UD_SLICE_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < P1_NBR_MOVE; ++y)
            UDSlice_MoveTable[i][y] = 0;
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
                UDSlice_MoveTable[raw][moveId] = UDSliceCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::generateFlipUDSliceRep()
{
    int repId(-1);

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
        }

        if (i == 16)
            FlipUDSlice_SymRep[++repId] = raw;
    }
    printf("RepId : %d\n", repId);
}

void    Kociemba::getFLipUDSliceRep()
{
    std::ifstream fileP1;
    fileP1.open(std::string("./data/flipUDSlice_Rep").c_str());
    if (fileP1)
    {
        fileP1.seekg(0, std::ios::end);
        size_t length = fileP1.tellg();
        fileP1.seekg(0, std::ios::beg);
        if (length > 257720 )
        {
            length = 257720 ;
        }
        fileP1.read((char*)FlipUDSlice_SymRep.data(), length);
    }
    else
    {
        generateFlipUDSliceRep();

        std::fstream file;
        file.open(std::string("./data/flipUDSlice_Rep").c_str(), std::fstream::out);
        file.write((char*)FlipUDSlice_SymRep.data(), 257720 );
        file.close();
    }
}

void    Kociemba::generate_FlipUDSlice_MoveTable()
{
    FlipUDSlice_MoveTable.resize(1013760);
    FlipUDSlice_Sym.resize(FLIP_UD_SLICE_MOVETABLE_SIZE);

    getFLipUDSliceRep();

    size_t repId(0);

    for (unsigned int raw = 0; raw < FLIP_UD_SLICE_MOVETABLE_SIZE; ++raw)
    {
        if (raw == FlipUDSlice_SymRep[repId])
        {
            struct edges Coord;
            Coord.o = generateEdgeOrientation(raw / UD_SLICE_MOVETABLE_SIZE);
            Coord.p = generateUDSlice(raw % UD_SLICE_MOVETABLE_SIZE);

            for (int sym = 0; sym < 16; ++sym)
            {
                struct edges tmpCoord = Coord;

                tmpCoord = Cube::multEdges(Cube::multEdges(symCubes[sym].m_edges, tmpCoord), symInvCubes[sym].m_edges);

                unsigned int coord = edgeOrientationCoordinates(tmpCoord.o) * UD_SLICE_MOVETABLE_SIZE + UDSliceCoordinates(tmpCoord.p);                
                FlipUDSlice_Sym[coord].first = repId;
                FlipUDSlice_Sym[coord].second.push_back(sym);
            }
            repId++;
        }

        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                FlipUDSlice_MoveTable[raw][moveId] = EdgeOrientation_MoveTable[raw / UD_SLICE_MOVETABLE_SIZE][moveId] * UD_SLICE_MOVETABLE_SIZE + UDSlice_MoveTable[raw % UD_SLICE_MOVETABLE_SIZE][moveId];//;
                ++moveId;
            }
        }
    }
}

/* ===================== P2 ===================== */

void    Kociemba::generate_UDSliceSorted_MoveTable()
{
    UDSliceSorted_MoveTable.resize(UD_SLICE_SORTED_MOVETABLE_SIZE);
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < 18; ++y)
            UDSliceSorted_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < UD_SLICE_SORTED_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateUDSliceSorted(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                UDSliceSorted_MoveTable[raw][moveId] = UDSliceSortedCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::generate_FBSliceSorted_MoveTable()
{
    FBSliceSorted_MoveTable.resize(UD_SLICE_SORTED_MOVETABLE_SIZE);
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < 18; ++y)
            FBSliceSorted_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < UD_SLICE_SORTED_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateFBSliceSorted(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                FBSliceSorted_MoveTable[raw][moveId] = FBSliceSortedCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::generate_RLSliceSorted_MoveTable()
{
    RLSliceSorted_MoveTable.resize(UD_SLICE_SORTED_MOVETABLE_SIZE);
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < 18; ++y)
            RLSliceSorted_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < UD_SLICE_SORTED_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateRLSliceSorted(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                RLSliceSorted_MoveTable[raw][moveId] = RLSliceSortedCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }
}

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
            //printf(" %5d : [ ", raw);
            for (int i = 0; i < 16; ++i)
            {
                std::array< CORNERS, 8 >    tmp;
                tmp = Cube::multCornPerm( Cube::multCornPerm(symCubes[i].m_corners.p, cornPerm), symInvCubes[i].m_corners.p );
                unsigned int coord = cornerPermutationCoordinates(tmp);
                
                //printf(" %5d ", coord);
                CornPerm_Sym[coord].first = repId;
                CornPerm_Sym[coord].second.push_back(i);
            }
           // printf("]\n");
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

void    Kociemba::generate_P2UDSlice_MoveTable()
{
    for (int i = 0; i < P2_UD_SLICE_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < 18; ++y)
            P2UDSlice_MoveTable[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < P2_UD_SLICE_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateP2UDSlice(raw);
        unsigned int moveId = 0;
        for (unsigned int rotateId = 0; rotateId < 6; ++rotateId)
        {
            std::array<EDGES, 12> edgePermRotated = edgePerm;
            for (unsigned int nbrRotate = 0; nbrRotate < 3 ; ++nbrRotate)
            {
                edgePermRotated = Cube::rotateEdgePerm(edgePermRotated, rotateId);
                P2UDSlice_MoveTable[raw][moveId] = P2UDSliceCoordinates(edgePermRotated);
                ++moveId;
            }
        }
    }
}

void    Kociemba::generateEdge8Perm()
{
    edge8Perm.resize(11880);
    for (int i = 0; i < UD_SLICE_SORTED_MOVETABLE_SIZE; ++i)
    {
        for (int y = 0; y < 24; ++y)
            edge8Perm[i][y] = 0;
    }

    for (unsigned int raw = 0; raw < P2_EDGE_PERMUTATION_MOVETABLE_SIZE; ++raw)
    {
        std::array<EDGES, 12> edgePerm = generateP2EdgePermutation(raw);
        unsigned int RLSliceSortedCoord = RLSliceSortedCoordinates(edgePerm);//the RLSliceSortedCoord
        unsigned int FBSliceSortedCoord = FBSliceSortedCoordinates(edgePerm);//the FBSliceSortedCoord
        edge8Perm[RLSliceSortedCoord][FBSliceSortedCoord % 24] = raw;
    }
}

int     Kociemba::generate_moveTables()
{
    generate_CornerOrientation_MoveTable();
    generate_EdgeOrientation_MoveTable();
    generate_UDSlice_MoveTable();
    generate_FlipUDSlice_MoveTable();

    generate_UDSliceSorted_MoveTable();
    generate_FBSliceSorted_MoveTable();
    generate_RLSliceSorted_MoveTable();

    generate_CornerPermutation_MoveTable();
    generate_P2EdgePermutation_MoveTable();
    generate_P2UDSlice_MoveTable();

    generateEdge8Perm();

    return (0);
}



