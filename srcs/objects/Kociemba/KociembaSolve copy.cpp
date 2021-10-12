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

int minSol = 2147483647;
int firstSol = 2147483647;
int P1Found = 10000;

std::vector<bool>   P1Path = {};
size_t              P1PathId(0);

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

    if (firstSol == 2147483647)
        firstSol = solution.path.size() ;

    if (solution.path.size() < minSol)
        minSol = solution.path.size();

    P1Path[solution.p2.P1PathId] = true;

    size_t count(0);

    Cube tmp = rubik;

    std::printf("\n Opened = %zu | %2lu : ", nbrOpenedStates, solution.path.size());
    for (auto it = solution.path.begin(); it != solution.path.end(); ++it)
    {
        std::printf("%-2s ", moves[*it].c_str());
        if (count == solution.p1.length)
            printf("[] ");
        tmp.move(moves[*it].c_str());
        count++;
    }
    //std::printf("\n");
}

void    Kociemba::generateChilds(std::priority_queue<SolvingState>& open, std::unordered_set<size_t>& close, SolvingState& current, const Cube& rubik)
{
    if (minSol <= current.path.size() + current.depht)
        return ;

    for (int moveId = 0; moveId < 18; ++moveId)
    {
        if ((current.lastMove != -1 && moveId / 3 == current.lastMove / 3) ||
            (current.phase == 2 && moveId / 3 != UP && moveId / 3 != DOWN && moveId % 3 != 1 ) ||
            current.phase == 2 && P1Path[current.p2.P1PathId])
            continue ;
        struct P1 phase1 = current.p1;
        struct P2 phase2 = current.p2;
        short phase = current.phase;
        int newDepht = current.depht;

        if (phase == 1)
        {
            phase1.length += 1;

            unsigned int newCornOrient = CornerOrientation_MoveTable[phase1.cornOrient][moveId];
            unsigned int newFlipUdSLice = FlipUdSlice_MoveTable[phase1.flipUdSlice][moveId];

            unsigned int newRep = FlipUdSlice_Sym[newFlipUdSLice].first;
            unsigned int newSym = FlipUdSlice_Sym[newFlipUdSLice].second[0];

            unsigned int newCornOrientSym = CornOrientSym_MoveTable[newCornOrient][newSym];

            unsigned int newCornPerm = CornerPermutation_MoveTable[phase2.cornPerm][moveId];

            // if (pruneDiff(phase1.depht, getValue_P1_PruneTable(newRep  * 2187 + newCornOrientSym)) == 0)
            //     newDepht -= 1;
            
            newDepht += pruneDiff(phase1.depht, getValue_P1_PruneTable(newRep  * 2187 + newCornOrientSym))
                        ;//+ (getValue_CornPerm_DephtTable(newCornPerm) - getValue_CornPerm_DephtTable(phase2.cornPerm));

            phase2.cornPerm = newCornPerm;
            
            // if (moveId / 3 == UP || moveId / 3 == DOWN || moveId % 3 == 1 )
            //     newDepht--;

            phase1.cornOrient = newCornOrient;
            phase1.flipUdSlice = newFlipUdSLice;
            phase1.depht = getValue_P1_PruneTable(newRep  * 2187 + newCornOrientSym);

            if (newFlipUdSLice == 0 && newCornOrient == 0)
            {
                phase = 2;
                P1Path.push_back(false);

                Cube tmp(rubik);
                for (auto it = current.path.begin(); it != current.path.end(); ++it)
                {
                    tmp.move(moveP1(*it).c_str());
                }
                tmp.move(moveP1(moveId).c_str());

                phase2.P1PathId = P1PathId++;

                phase2.cornPerm = cornerPermutationCoordinates(tmp.m_corners.p);
                phase2.edgePerm = phase2EdgePermutationCoordinates(tmp.m_edges.p);
                phase2.UDSlice = P2UDSliceCoordinates(tmp.m_edges.p);
                phase2.CPEP = getValue_P2_CPEP_PruneTable( P2EdgePermSym_MoveTable[phase2.edgePerm][CornPerm_Sym[phase2.cornPerm].second[0]] * 2768 + 
                                                            CornPerm_Sym[phase2.cornPerm].first );                          
                phase2.UDSliceDepht = getValue_P2UDSlice_DephtTable(phase2.UDSlice);
                //newDepht += getValue_CornPerm_DephtTable(phase2.cornPerm);//phase2.UDSliceDepht;
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
            unsigned int newUDSliceDepht = getValue_P2UDSlice_DephtTable(newP2UDSlice);

            // if (pruneDiff(phase2.CPEP, newCPEP) > 0)
            //     continue ;
            newDepht += pruneDiff(phase2.CPEP, newCPEP);// + (newUDSliceDepht - phase2.UDSliceDepht);
        
            phase2.cornPerm = newCornPerm;
            phase2.edgePerm = newEdgePerm;
            phase2.UDSlice = newP2UDSlice;
            phase2.CPEP = newCPEP;
            phase2.UDSliceDepht = newUDSliceDepht;
        }


        
        std::vector<int> newPath = current.path;
        newPath.push_back(moveId);
        size_t newIndex = hashPath(newPath);
        
        if (close.find( newIndex ) == close.end())
        {
            close.insert( newIndex );
            if (current.phase == 1 && phase == 2)
            {
                open.emplace(phase1, phase2, 2, newDepht + 1, newPath, moveId);
                open.emplace(phase1, phase2, 1, newDepht + 1, newPath, moveId);
            }
            else
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
    unsigned int P2UDSlice = P2UDSliceCoordinates(rubik.m_edges.p);

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
            P2UDSlice,
            getValue_P2_CPEP_PruneTable(P2EdgePermSym_MoveTable[edgePerm][CornPerm_Sym[cornPerm].second[0]] * 2768
                                            + CornPerm_Sym[cornPerm].first),
            getValue_P2UDSlice_DephtTable(P2UDSlice)
        ),
        phase
    );
    close.emplace( hashPath(open.top().path) );

    size_t  opened = 0;

    size_t  solFound = 2000;

    while (!open.empty())
    {
        SolvingState current = open.top();
        open.pop();

        /* ===== DEBUG ===== */

        // printf("%s %d :: %2d - ( %5u %8u | %5u %5u %5u ) %5u [%2lu]%s ",
        //         (current.phase == 1) ? RED : GREEN, current.phase, current.depht,
        //         current.p1.cornOrient, current.p1.flipUdSlice,
        //         current.p2.cornPerm, current.p2.edgePerm, current.p2.P2UDSlice, current.p2.UDSliceDepht,
        //         current.path.size(), RESET);
        // for (auto it = current.path.begin(); it != current.path.end(); ++it)
        // {
        //     std::printf(" %-2s ", moveP1(*it).c_str());
        // }
        // std::printf("\n");
        
        // opened++;

        /* ===== SOLVED ===== */

        if (current.phase == 2 && current.p2.cornPerm == 0 && current.p2.edgePerm == 0 && current.p2.P2UDSlice == 0)
        {
            solveSucess(rubik, current, opened);
            if ((--solFound) == 0)
            {
                printf("\n\n Min : %d - First : %d\n\n", minSol, firstSol);
                return ;
            }
        }

        /* ===== GENERATE ===== */

        else if (current.phase == 1)
        { if (P1Found) generateChilds(open, close, current, rubik); }
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
    unsigned int udSliceS = P2UDSliceCoordinates(rubik.m_edges.p);


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
    udSliceS = P2UDSliceCoordinates(rubik.m_edges.p);


    std::printf("CORNER ORIENTATION     : %u\n", cornOrient);
    std::printf("EDGE ORIENTATION       : %u\n", edgeOrient);
    std::printf("UD SLICE               : %u\n", udSlice);
    std::printf("CORNER PERMUTATION     : %u\n", cornPerm);
    std::printf("EDGE ORIENTATION       : %u\n", edgePerm);
    std::printf("UD SLICE SORTED        : %u\n", udSliceS);
}