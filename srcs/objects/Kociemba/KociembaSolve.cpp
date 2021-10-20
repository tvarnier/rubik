#include "Kociemba.hpp"

int minSol = 100;
int firstSol = 100;

size_t  hashPath(std::vector<int> path)
{
    size_t seed(0);
    std::hash<int>  hasher;

    for (const auto& move: path)
    {
        seed ^= hasher(move) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

int     pruneDiff(uint8_t currentDepht, uint8_t newDepht)
{
    if (currentDepht == 1 && newDepht == 3)
        return -1;
    else if (currentDepht == 3 && newDepht == 1)
        return +1;
    else
        return (newDepht - currentDepht);
}

bool     Kociemba::isStateUseless(const short& phase, const unsigned int& size, const P1& phase1, const P2& phase2)
{
    if (
        (phase == 1 && (unsigned int)(size + phase1.depht) > 12)
        // || (phase == 1 && (unsigned int)(phase1.nbrMove + phase1.depht + phase2.cornPermDepht) >= minSol)
        || (phase == 1 && (unsigned int)(size + ((phase1.depht > phase2.cornPermDepht) ? phase1.depht : phase2.cornPermDepht)) >= minSol)
        || (phase == 2 && (unsigned int)(size + phase2.depht) >= ((minSol < 31) ? minSol : 31))
    )
        return (true);
    return (false);
}

std::string moveP1(int i)
{
    std::string moves[18] = {
        "U", "U2", "U'",
        "R", "R2", "R'",
        "F", "F2", "F'",
        "D", "D2", "D'",
        "L", "L2", "L'",
        "B", "B2", "B'"
    };
    return (moves[i]);
}

void    Kociemba::solveSucess(const Cube& rubik, SolvingState& solution, size_t nbrOpenedStates)
{
    std::string moves[18] = {
        "U", "U2", "U'",
        "R", "R2", "R'",
        "F", "F2", "F'",
        "D", "D2", "D'",
        "L", "L2", "L'",
        "B", "B2", "B'"
    };

    if (firstSol == 100)
        firstSol = solution.path.size() ;

    if (solution.path.size() < minSol)
        minSol = solution.path.size();

    size_t count(0);

    Cube tmp = rubik;

    std::printf("   -> Opened = %zu | %2lu : ", nbrOpenedStates, solution.path.size());
    for (auto it = solution.path.begin(); it != solution.path.end(); ++it)
    {
        std::printf("%-2s ", moves[*it].c_str());
        tmp.move(moves[*it].c_str());
        count++;
    }
    std::printf("\n");
}

size_t  Kociemba::getP1Length(unsigned int cornOrient, unsigned int flipUDSlice, uint8_t pruning)
{
    for (int moveId = 0; moveId < 18; ++moveId)
    {
        unsigned int newCornOrient = CornerOrientation_MoveTable[cornOrient][moveId];
        unsigned int newFlipUDSlice = FlipUDSlice_MoveTable[flipUDSlice][moveId];

        unsigned int newRep = FlipUDSlice_Sym[newFlipUDSlice].first;
        unsigned int newSym = FlipUDSlice_Sym[newFlipUDSlice].second[0];

        unsigned int newCornOrientSym = CornOrientSym_MoveTable[newCornOrient][newSym];

        unsigned int newPruning = getValue_P1_PruneTable(newRep  * 2187 + newCornOrientSym);

        if (pruneDiff(pruning, newPruning) == -1)
            return (getP1Length(newCornOrient, newFlipUDSlice, newPruning) + 1);
    }
    return (0);
}

size_t  Kociemba::getP2Length(unsigned int cornPerm, unsigned int edgePerm, uint8_t pruning)
{
    for (int moveId = 0; moveId < 18; ++moveId)
    {
        if (moveId / 3 != ROT_UP && moveId / 3 != ROT_DOWN && moveId % 3 != 1 )
            continue ;
        unsigned int newCornPerm = CornerPermutation_MoveTable[cornPerm][moveId];
        unsigned int newEdgePerm = P2EdgePermutation_MoveTable[edgePerm][moveId];

        unsigned int newRep = CornPerm_Sym[newCornPerm].first;
        unsigned int newSym = CornPerm_Sym[newCornPerm].second[0];

        unsigned int newEdgePermSym = P2EdgePermSym_MoveTable[newEdgePerm][newSym];

        unsigned int newPruning = getValue_P2_CPEP_PruneTable(newEdgePermSym  * 2768  + newRep);

        if (pruneDiff(pruning, newPruning) == -1)
            return (getP2Length(newCornPerm, newEdgePerm, newPruning) + 1);
    }
    return (0);
}

void    Kociemba::generateChilds(std::set<SolvingState>& open, std::unordered_set<size_t>& close, SolvingState& current, const Cube& rubik)
{
    // printf("            %s[\n", GREY);
    for (int moveId = 0; moveId < 18; ++moveId)
    {
        if ((current.lastMove != -1 && moveId / 3 == current.lastMove / 3) ||
            (current.phase == 2 && moveId / 3 != ROT_UP && moveId / 3 != ROT_DOWN && moveId % 3 != 1 ))
            continue ;
        struct P1 phase1 = current.p1;
        struct P2 phase2 = current.p2;
        short phase = current.phase;
        int newDepht = current.depht;

        if (phase == 1)
        {
            if (moveId / 3 != ROT_UP && moveId / 3 != ROT_DOWN && moveId % 3 != 1 )
                phase1.nbrMove++;

            unsigned int newCornOrient = CornerOrientation_MoveTable[phase1.cornOrient][moveId];
            unsigned int newFlipUDSlice = FlipUDSlice_MoveTable[phase1.flipUDSlice][moveId];

            unsigned int newRep = FlipUDSlice_Sym[newFlipUDSlice].first;
            unsigned int newSym = FlipUDSlice_Sym[newFlipUDSlice].second[0];

            unsigned int newCornOrientSym = CornOrientSym_MoveTable[newCornOrient][newSym];

            int pruneDiffP1(pruneDiff(phase1.pruning, getValue_P1_PruneTable(newRep  * 2187 + newCornOrientSym)));
            
            newDepht += (pruneDiffP1 * 2);
            phase1.depht += pruneDiffP1;

            phase1.cornOrient = newCornOrient;
            phase1.flipUDSlice = newFlipUDSlice;
            phase1.pruning = getValue_P1_PruneTable(newRep  * 2187 + newCornOrientSym);

            phase1.UDSliceSorted = UDSliceSorted_MoveTable[phase1.UDSliceSorted][moveId];
            phase1.RLSliceSorted = RLSliceSorted_MoveTable[phase1.RLSliceSorted][moveId];
            phase1.FBSliceSorted = FBSliceSorted_MoveTable[phase1.FBSliceSorted][moveId];

            phase2.cornPerm = CornerPermutation_MoveTable[phase2.cornPerm][moveId];
            phase2.cornPermDepht = getValue_CornPerm_DephtTable(phase2.cornPerm);

            if (newFlipUDSlice == 0 && newCornOrient == 0)
            {
                phase = 2;
                phase2.edgePerm = edge8Perm[phase1.RLSliceSorted][phase1.FBSliceSorted % 24];
                phase2.UDSlice = phase1.UDSliceSorted % 24;
                phase2.CPEP = getValue_P2_CPEP_PruneTable( P2EdgePermSym_MoveTable[phase2.edgePerm][CornPerm_Sym[phase2.cornPerm].second[0]] * 2768 + 
                                                            CornPerm_Sym[phase2.cornPerm].first );
                phase2.CPUS = getValue_P2_CPUS_PruneTable(phase2.cornPerm * P2_UD_SLICE_MOVETABLE_SIZE + phase2.UDSlice);
                phase2.USEP = getValue_P2_USEP_PruneTable(phase2.UDSlice * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + phase2.edgePerm);

                phase2.depht = getP2Length(phase2.cornPerm, phase2.edgePerm, phase2.CPEP);
            }
        }
        else if (phase == 2)
        {
            unsigned int newCornPerm = CornerPermutation_MoveTable[phase2.cornPerm][moveId];
            unsigned int newEdgePerm = P2EdgePermutation_MoveTable[phase2.edgePerm][moveId];
            unsigned int newP2UDSlice = P2UDSlice_MoveTable[phase2.UDSlice][moveId];

            unsigned int newRep = CornPerm_Sym[newCornPerm].first;
            unsigned int newSym = CornPerm_Sym[newCornPerm].second[0];

            unsigned int newEdgePermSym = P2EdgePermSym_MoveTable[newEdgePerm][newSym];

            unsigned int newCPEP = getValue_P2_CPEP_PruneTable(newEdgePermSym  * 2768  + newRep);
            unsigned int newCPUS = getValue_P2_CPUS_PruneTable(newCornPerm * P2_UD_SLICE_MOVETABLE_SIZE + newP2UDSlice);
            unsigned int newUSEP = getValue_P2_USEP_PruneTable(newP2UDSlice * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);

            // if (pruneDiff(phase2.CPEP, newCPEP) != -1)
            //     continue;
            unsigned int pruneDiffP2 = pruneDiff(phase2.CPEP, newCPEP);
            
            newDepht += (pruneDiffP2 * 2);// + pruneDiff(phase2.CPUS, newCPUS) + pruneDiff(phase2.USEP, newUSEP);
            phase2.depht += pruneDiffP2;
        
            phase2.cornPerm = newCornPerm;
            phase2.edgePerm = newEdgePerm;
            phase2.UDSlice = newP2UDSlice;
            phase2.CPEP = newCPEP;
            phase2.CPUS = newCPUS;
            phase2.USEP = newUSEP;
        }

        if ( isStateUseless(phase, current.path.size() + 1, phase1, phase2) )
        {
                // printf("                %2s -> PHASE : %d [ S:%2u; P1D:%2u; P2D:%2u; P2_CPD:%2u ]\n", moveP1(moveId).c_str(), phase, current.path.size() + 1, phase1.depht, phase2.depht, phase2.cornPermDepht);
                continue ;
        }
        
        std::vector<int> newPath = current.path;
        newPath.push_back(moveId);
        size_t newIndex = hashPath(newPath);

        
        if (close.find( newIndex ) == close.end())
        {
            close.insert( newIndex );
            open.emplace(phase1, phase2, phase, newDepht + 1, newPath, newIndex, moveId);
            // if (open.emplace(phase1, phase2, phase, newDepht + 1, newPath, newIndex, moveId).second == true)
            //     printf(" %2s(%d)", moveP1(moveId).c_str(), newDepht + 1);

        
        }
    }
    // printf("            ]%s\n", RESET);
}

void    Kociemba::solveP1(Cube& rubik)
{
    std::set<SolvingState>  open;
    std::unordered_set<size_t>  close;

    unsigned int cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    unsigned int EdgeOrient = edgeOrientationCoordinates(rubik.m_edges.o);
    unsigned int UDSlice = UDSliceCoordinates(rubik.m_edges.p);
    unsigned int flipUDSlice = EdgeOrient * UD_SLICE_MOVETABLE_SIZE + UDSlice;

    unsigned int cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    unsigned int edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    unsigned int P2UDSlice = P2UDSliceCoordinates(rubik.m_edges.p);

    unsigned int P1Pruning = getValue_P1_PruneTable(FlipUDSlice_Sym[flipUDSlice].first * CORNER_ORIENTATION_MOVETABLE_SIZE
                                    + CornOrientSym_MoveTable[cornOrient][FlipUDSlice_Sym[flipUDSlice].second[0]]);
    unsigned int P2_CPEP_Pruning = getValue_P2_CPEP_PruneTable(P2EdgePermSym_MoveTable[edgePerm][CornPerm_Sym[cornPerm].second[0]] * 2768
                                            + CornPerm_Sym[cornPerm].first);

    short phase(1);
    if (cornOrient == 0 && flipUDSlice == 0)
        phase = 2;

    open.emplace(
        P1(
            cornOrient,
            flipUDSlice,
            UDSliceSortedCoordinates(rubik.m_edges.p),
            RLSliceSortedCoordinates(rubik.m_edges.p),
            FBSliceSortedCoordinates(rubik.m_edges.p),
            P1Pruning,
            getP1Length(cornOrient, flipUDSlice, P1Pruning)
        ),
        P2(
            cornPerm,
            edgePerm,
            P2UDSlice,
            P2_CPEP_Pruning,
            getValue_P2_CPUS_PruneTable(cornPerm * P2_UD_SLICE_MOVETABLE_SIZE + P2UDSlice),
            getValue_P2_USEP_PruneTable(P2UDSlice * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + edgePerm),
            getP2Length(cornPerm, edgePerm, P2_CPEP_Pruning),
            getValue_CornPerm_DephtTable(cornPerm)
        ),
        phase
    );
    close.emplace( hashPath(open.begin()->path) );

    size_t  opened = 0;

    auto overMinSol = [this](auto const& x) {
        // for (auto it = x.path.begin(); it != x.path.end(); ++it)
        // {
        //     std::printf(" %-2s ", moveP1(*it).c_str());
        // }
        // std::printf("\n");
        // if (isStateUseless(x.phase, x.path.size(), x.p1, x.p2))
        //     printf(" PHASE : %d [ S:%2u; P1D:%2u; P2D:%2u; P2_CPD:%2u ]\n", x.phase, x.path.size(), x.p1.depht, x.p2.depht, x.p2.cornPermDepht);
        return( isStateUseless(x.phase, x.path.size(), x.p1, x.p2) );
    };

    while (!open.empty())
    {
        // if ( (open.begin()->phase == 1 && (unsigned int)(open.begin()->path.size() + open.begin()->p1.depht) > 12)
        //     || (open.begin()->phase == 1 && (unsigned int)(open.begin()->path.size() +  ((open.begin()->p1.depht > open.begin()->p2.cornPermDepht) ? open.begin()->p1.depht : open.begin()->p2.cornPermDepht)) >= minSol)
        //     || (open.begin()->phase == 2 && (unsigned int)(open.begin()->path.size() + open.begin()->p2.depht) >= ((minSol < 31) ? minSol : 31)))
        // {
        //     printf(" > POP\n");

        //     printf("%s %10d :: %2d - ( %5u %8u | %5u %5u %5u ) [%2lu] %2u + %2u %s ",
        //         (open.begin()->phase == 1) ? RED : GREEN, minSol, open.begin()->depht,
        //         open.begin()->p1.cornOrient, open.begin()->p1.flipUDSlice,
        //         open.begin()->p2.cornPerm, open.begin()->p2.edgePerm, open.begin()->p2.UDSlice,
        //         open.begin()->path.size(), open.begin()->p1.depht, open.begin()->p2.depht, RESET);
        //     for (auto it = open.begin()->path.begin(); it != open.begin()->path.end(); ++it)
        //     {
        //         std::printf(" %-2s ", moveP1(*it).c_str());
        //     }
        //     std::printf("\n");

        //     open.erase(open.begin());
        //     continue ;
        // }
        SolvingState current = *(open.begin());
        open.erase(open.begin());

        /* ===== DEBUG ===== */
        if (minSol <= current.path.size())
            continue ;

        // printf("%s %10d :: %d %2d - ( %5u %8u | %5u %5u %5u ) [%2lu] %2u + %2u + %2u %s      ||      ",
        //         (current.phase == 1) ? RED : GREEN, minSol, current.phase, current.depht,
        //         current.p1.cornOrient, current.p1.flipUDSlice,
        //         current.p2.cornPerm, current.p2.edgePerm, current.p2.UDSlice,
        //         current.path.size(), current.p1.depht, current.p2.depht, current.p2.cornPermDepht, RESET);
        // for (auto it = current.path.begin(); it != current.path.end(); ++it)
        // {
        //     std::printf(" %-2s ", moveP1(*it).c_str());
        // }
        // std::printf("\n");
        
        opened++;

        if (current.phase == 2 && current.p2.cornPerm == 0 && current.p2.edgePerm == 0 && current.p2.UDSlice == 0)
        {
            solveSucess(rubik, current, opened);
            std::erase_if(open,overMinSol);
            // if ((--solFound) == 0)
            // {
            //     return ;
            // }
        }
        else
            generateChilds(open, close, current, rubik);
    }
    printf("\n\n Min : %d - First : %d\n\n", minSol, firstSol);
}

void    Kociemba::solve(Cube rubik)
{
    unsigned int cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    unsigned int edgeOrient = edgeOrientationCoordinates(rubik.m_edges.o);
    unsigned int UDSlice = UDSliceCoordinates(rubik.m_edges.p);
    unsigned int cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    unsigned int edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    unsigned int UDSliceS = P2UDSliceCoordinates(rubik.m_edges.p);


    std::printf("CORNER ORIENTATION     : %u\n", cornOrient);
    std::printf("EDGE ORIENTATION       : %u\n", edgeOrient);
    std::printf("UD SLICE               : %u\n", UDSlice);
    std::printf("CORNER PERMUTATION     : %u\n", cornPerm);
    std::printf("EDGE ORIENTATION       : %u\n", edgePerm);
    std::printf("P2 UD SLICE            : %u\n", UDSliceS);

    solveP1(rubik);

    cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    edgeOrient = edgeOrientationCoordinates(rubik.m_edges.o);
    UDSlice = UDSliceCoordinates(rubik.m_edges.p);
    cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    UDSliceS = P2UDSliceCoordinates(rubik.m_edges.p);


    std::printf("CORNER ORIENTATION     : %u\n", cornOrient);
    std::printf("EDGE ORIENTATION       : %u\n", edgeOrient);
    std::printf("UD SLICE               : %u\n", UDSlice);
    std::printf("CORNER PERMUTATION     : %u\n", cornPerm);
    std::printf("EDGE ORIENTATION       : %u\n", edgePerm);
    std::printf("P2 UD SLICE            : %u\n", UDSliceS);
}