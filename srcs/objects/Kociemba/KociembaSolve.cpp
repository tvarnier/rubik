#include "Kociemba.hpp"

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

void    Kociemba::solveSucess(Cube& rubik, SolvingState& solution, size_t& nbrOpenedStates)
{
    std::string moves[18] = {
        "U", "U2", "U'",
        "R", "R2", "R'",
        "F", "F2", "F'",
        "D", "D2", "D'",
        "L", "L2", "L'",
        "B", "B2", "B'"
    };

    std::printf("\n Opened = %zu | %lu : ", nbrOpenedStates, solution.path.size());
    for (auto it = solution.path.begin(); it != solution.path.end(); ++it)
    {
        std::printf("%s ", moves[*it].c_str());
        rubik.move(moves[*it].c_str());
    }
    std::printf("\n");
}

unsigned int limitP1 = 10000000;

void    Kociemba::generateChilds(std::priority_queue<SolvingState>& open, std::unordered_set<size_t>& close, SolvingState& current, const Cube& rubik)
{
    for (int moveId = 0; moveId < 18; ++moveId)
    {
        if ((current.lastMove != -1 && moveId / 3 == current.lastMove / 3) ||
            (current.phase == 2 && moveId / 3 != UP && moveId / 3 != DOWN && moveId % 3 != 1 ))
            continue ;
        struct P1 phase1 = current.p1;
        struct P2 phase2 = current.p2;
        short phase = current.phase;
        int newDepht = current.depht;

        if (phase == 1)
        {
            unsigned int newCornOrient = CornerOrientation_MoveTable[phase1.cornOrient][moveId];
            unsigned int newFlipUdSLice = FlipUdSlice_MoveTable[phase1.flipUdSlice][moveId];

            unsigned int newRep = FlipUdSlice_Sym[newFlipUdSLice].first;
            unsigned int newSym = FlipUdSlice_Sym[newFlipUdSLice].second[0];

            unsigned int newCornOrientSym = CornOrientSym_MoveTable[newCornOrient][newSym];
            newDepht += pruneDiff(phase1.depht, getValue_P1_PruneTable(newRep  * 2187 + newCornOrientSym));

            phase1.cornOrient = newCornOrient;
            phase1.flipUdSlice = newFlipUdSLice;
            phase1.depht = getValue_P1_PruneTable(newRep  * 2187 + newCornOrientSym);

            if (newFlipUdSLice == 0 && newCornOrient == 0)
            {
                phase = 2;

                Cube tmp(rubik);
                for (auto it = current.path.begin(); it != current.path.end(); ++it)
                {
                    tmp.move(moveP1(*it).c_str());
                }
                tmp.move(moveP1(moveId).c_str());

                phase2.cornPerm = cornerPermutationCoordinates(tmp.m_corners.p);
                phase2.edgePerm = phase2EdgePermutationCoordinates(tmp.m_edges.p);
                phase2.udSliceSorted = UDSliceSortedCoordinates(tmp.m_edges.p);
                phase2.CPEP = getValue_P2_CPEP_PruneTable( P2EdgePermSym_MoveTable[phase2.edgePerm][CornPerm_Sym[phase2.cornPerm].second[0]] * 2768 + 
                                                            CornPerm_Sym[phase2.cornPerm].first );                          
                phase2.udSliceSortedDepht = getValue_UdSliceSorted_DephtTable(phase2.udSliceSorted);
                newDepht += getValue_CornPerm_DephtTable(phase2.cornPerm);
            }
        }
        else if (phase == 2)
        {
            unsigned int newCornPerm = CornerPermutation_MoveTable[phase2.cornPerm][moveId];
            unsigned int newEdgePerm = P2EdgePermutation_MoveTable[phase2.edgePerm][moveId];
            unsigned int newUdSliceSorted = UdSliceSorted_MoveTable[phase2.udSliceSorted][moveId];

            unsigned int newRep = CornPerm_Sym[newCornPerm].first;
            unsigned int newSym = CornPerm_Sym[newCornPerm].second[0];

            unsigned int newEdgePermSym = P2EdgePermSym_MoveTable[newEdgePerm][newSym];

            unsigned int newCPEP = getValue_P2_CPEP_PruneTable(newEdgePermSym  * 2768  + newRep);
            unsigned int newUdSliceSortedDepht = getValue_UdSliceSorted_DephtTable(newUdSliceSorted);

            if (pruneDiff(phase2.CPEP, newCPEP) > 0)
                continue ;
            newDepht += pruneDiff(phase2.CPEP, newCPEP) + (newUdSliceSortedDepht - phase2.udSliceSortedDepht);
        
            phase2.cornPerm = newCornPerm;
            phase2.edgePerm = newEdgePerm;
            phase2.udSliceSorted = newUdSliceSorted;
            phase2.CPEP = newCPEP;
            phase2.udSliceSortedDepht = newUdSliceSortedDepht;
        }


        
        std::vector<int> newPath = current.path;
        newPath.push_back(moveId);
        size_t newIndex = hashPath(newPath);
        
        if (close.find( newIndex ) == close.end())
        {
            close.insert( newIndex );
            open.emplace(phase1, phase2, phase, newDepht + 1, newPath, moveId);
        }
    }
}

void    Kociemba::solveP1(Cube& rubik)
{

    std::priority_queue<SolvingState>  open;
    std::unordered_set<size_t>  close;

    unsigned int cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    unsigned int EdgeOrient = edgeOrientationCoordinates(rubik.m_edges.o);
    unsigned int UdSlice = UDSliceCoordinates(rubik.m_edges.p);
    unsigned int flipUdSlice = EdgeOrient * UD_SLICE_MOVETABLE_SIZE + UdSlice;

    unsigned int cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    unsigned int edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    unsigned int udSliceSorted = UDSliceSortedCoordinates(rubik.m_edges.p);

    short phase(1);
    if (cornOrient == 0 && flipUdSlice == 0)
        phase = 2;

    open.emplace(
        P1(
            cornOrient,
            flipUdSlice,
            getValue_P1_PruneTable(FlipUdSlice_Sym[flipUdSlice].first * CORNER_ORIENTATION_MOVETABLE_SIZE
                                    + CornOrientSym_MoveTable[cornOrient][FlipUdSlice_Sym[flipUdSlice].second[0]])
        ),
        P2(
            cornPerm,
            edgePerm,
            udSliceSorted,
            getValue_P2_CPEP_PruneTable(P2EdgePermSym_MoveTable[edgePerm][CornPerm_Sym[cornPerm].second[0]] * 2768
                                            + CornPerm_Sym[cornPerm].first),
            getValue_UdSliceSorted_DephtTable(udSliceSorted)
        ),
        phase
    );
    close.emplace( hashPath(open.top().path) );

    size_t  opened = 0;

    while (!open.empty())
    {
        SolvingState current = open.top();
        open.pop();

        /* ===== DEBUG ===== */

        printf("%s %d :: %2d - ( %5u %8u | %5u %5u %5u ) %5u [%2lu]%s ",
                (current.phase == 1) ? RED : GREEN, current.phase, current.depht,
                current.p1.cornOrient, current.p1.flipUdSlice,
                current.p2.cornPerm, current.p2.edgePerm, current.p2.udSliceSorted, current.p2.udSliceSortedDepht,
                current.path.size(), RESET);
        for (auto it = current.path.begin(); it != current.path.end(); ++it)
        {
            std::printf(" %-2s ", moveP1(*it).c_str());
        }
        std::printf("\n");
        
        opened++;

        /* ===== SOLVED ===== */

        if (current.phase == 2 && current.p2.cornPerm == 0 && current.p2.edgePerm == 0 && current.p2.udSliceSorted == 0)
        {
            solveSucess(rubik, current, opened);
            return ;
        }

        /* ===== GENERATE ===== */

        else if (current.phase == 1)
        { if (limitP1) { generateChilds(open, close, current, rubik); } }
        else
            generateChilds(open, close, current, rubik);

    }
}

void    Kociemba::solve(Cube rubik)
{
    unsigned int cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    unsigned int edgeOrient = edgeOrientationCoordinates(rubik.m_edges.o);
    unsigned int udSlice = UDSliceCoordinates(rubik.m_edges.p);
    unsigned int cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    unsigned int edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    unsigned int udSliceS = UDSliceSortedCoordinates(rubik.m_edges.p);


    std::printf("CORNER ORIENTATION     : %u\n", cornOrient);
    std::printf("EDGE ORIENTATION       : %u\n", edgeOrient);
    std::printf("UD SLICE               : %u\n", udSlice);
    std::printf("CORNER PERMUTATION     : %u\n", cornPerm);
    std::printf("EDGE ORIENTATION       : %u\n", edgePerm);
    std::printf("UD SLICE SORTED        : %u\n", udSliceS);

    solveP1(rubik);

    cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    edgeOrient = edgeOrientationCoordinates(rubik.m_edges.o);
    udSlice = UDSliceCoordinates(rubik.m_edges.p);
    cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    udSliceS = UDSliceSortedCoordinates(rubik.m_edges.p);


    std::printf("CORNER ORIENTATION     : %u\n", cornOrient);
    std::printf("EDGE ORIENTATION       : %u\n", edgeOrient);
    std::printf("UD SLICE               : %u\n", udSlice);
    std::printf("CORNER PERMUTATION     : %u\n", cornPerm);
    std::printf("EDGE ORIENTATION       : %u\n", edgePerm);
    std::printf("UD SLICE SORTED        : %u\n", udSliceS);
}