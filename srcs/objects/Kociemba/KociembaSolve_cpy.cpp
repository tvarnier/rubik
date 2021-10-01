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

int     Kociemba::Phase2Depht(unsigned int cornPerm, unsigned int edgePerm, unsigned int udSliceSorted)
{ return (CornerPermutation_DephtTable[cornPerm] + EdgePermutation_DephtTable[edgePerm] + UdSliceSorted_DephtTable[udSliceSorted]); }

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

void    Kociemba::solveSucess(Cube& rubik, State& solution, size_t& nbrOpenedStates)
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

size_t  countP2 = 2000;

void    Kociemba::generateP1(std::priority_queue<State>& open, std::unordered_set<size_t>& close, State& current, const Cube& rubik)
{
    for (int i = 0; i < 18; ++i)
    {
        if (current.phase == 2 && (i / 3 == RIGHT || i / 3 == FRONT || i / 3 == LEFT || i / 3 == BACK)
            && (i % 3 == 0 || i % 3 == 2))
                continue ;

        unsigned int newCornOrient  = current.cornOrient;
        unsigned int newFlipUdSlice = current.flipUdSlice;
        
        uint8_t     newP1Depht = current.P1Depht;

        unsigned int newCornPerm        = current.cornPerm;
        unsigned int newEdgePerm        = current.edgePerm;
        unsigned int newUdSliceSorted   = current.udSliceSorted;

        uint8_t     newP2Depht = current.P2Depht;

        int          newDepht   = current.depht;
        size_t       newIndex   = 0;
        short        phase      = current.phase;

        newCornOrient   = CornerOrientation_MoveTable[current.cornOrient][i];
        newFlipUdSlice  = FlipUdSlice_MoveTable[current.flipUdSlice][i];

        newP1Depht = getValue_P1_PruneTable(FlipUdSlice_Sym[newFlipUdSlice].first * CORNER_ORIENTATION_MOVETABLE_SIZE
                                            + CornOrientSym_MoveTable[newCornOrient][FlipUdSlice_Sym[newFlipUdSlice].second[0]]);
        
        
        newCornPerm        = CornerPermutation_MoveTable[current.cornPerm][i];

        if (phase == 1 && newCornOrient == 0 && newFlipUdSlice == 0)
        {
            countP2--;
            phase = 2;
            Cube tmp(rubik);
            for (auto it = current.path.begin(); it != current.path.end(); ++it)
            {
                tmp.move(moveP1(*it).c_str());
            }
            tmp.move(moveP1(i).c_str());
            newCornPerm = cornerPermutationCoordinates(tmp.m_corners.p);
            newEdgePerm = phase2EdgePermutationCoordinates(tmp.m_edges.p);
            newUdSliceSorted = UDSliceSortedCoordinates(tmp.m_edges.p);
            newP2Depht = getValue_P2_PruneTable(CornPerm_Sym[newCornPerm].first * P2_EDGE_PERMUTATION_MOVETABLE_SIZE
                                                + P2EdgePermSym_MoveTable[newEdgePerm][CornPerm_Sym[newCornPerm].second[0]]);
            newDepht = current.depht + (pruneDiff(current.P2Depht, newP2Depht));
        }
        else if (phase == 1)
        {
            newDepht = current.depht + (pruneDiff(current.P1Depht, newP1Depht));
        }
        else if (phase == 2)
        {
            newEdgePerm        = P2EdgePermutation_MoveTable[current.edgePerm][i];
            newUdSliceSorted   = UdSliceSorted_MoveTable[current.udSliceSorted][i];
            newP2Depht = getValue_P2_PruneTable(CornPerm_Sym[newCornPerm].first * P2_EDGE_PERMUTATION_MOVETABLE_SIZE
                                                + P2EdgePermSym_MoveTable[newEdgePerm][CornPerm_Sym[newCornPerm].second[0]]);
            newDepht = current.depht + (pruneDiff(current.P2Depht, newP2Depht));
        }

        std::vector<int> newPath = current.path;
        newPath.push_back(i);
        newIndex = hashPath(newPath);
        
        if (close.find( newIndex ) == close.end())
        {
            close.insert( newIndex );
            open.emplace(newCornOrient, newFlipUdSlice, newP1Depht,
                         newCornPerm, newEdgePerm, newUdSliceSorted, newP2Depht,
                         phase, newDepht + 1, newPath);
        }
    }
}

void    Kociemba::generateP2(std::priority_queue<State>& open, std::unordered_set<size_t>& close, State& current)
{
    // std::vector<State>  bestStates;
    // int     minDepht = 2147483647;
    // size_t  newIndex = 0;

    // int moveId = 0;
    // for (int i = 0; i < 18; ++i)
    // {
        

    //     unsigned int newCornPerm  = current.cornPerm;
    //     unsigned int newEdgePerm  = current.edgePerm;
    //     unsigned int newUdSliceSorted   = current.udSliceSorted;
    //     uint8_t      newCPEP  = current.CPEP;
    //     uint8_t      newCPUS  = current.CPUS;
    //     uint8_t      newUSEP  = current.USEP;

    //     int          newDepht = current.depht;
    //     short        phase = current.phase;

    //     newCornPerm        = CornerPermutation_MoveTable[current.cornPerm][i];
    //     newCPEP  = getValue_P2_CPEP_PruneTable(newCornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
    //     newCPUS  = getValue_P2_CPUS_PruneTable(newCornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + newUdSlice);
    //     newUSEP  = getValue_P2_USEP_PruneTable(newUdSliceSorted * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
    
    //     int newPruneDiff((pruneDiff(current.CPEP, newCPEP) + pruneDiff(current.CPUS, newCPUS) + pruneDiff(current.USEP, newUSEP)));

    //     if (newPruneDiff > 0) { newPruneDiff *= 3; }

    //     newDepht = current.depht + newPruneDiff;

    //     // if (newDepht < minDepht)
    //     // {
    //     //     minDepht = newDepht;
    //     //     bestStates.clear();
    //     // }
    //     // if (newDepht == minDepht)
    //     // {
    //     //     std::vector<int> newPath = current.path;
    //     //     newPath.push_back(i);

    //     //     bestStates.emplace_back( newCornOrient, newEdgeOrient, newUdSlice, newCOEO, newCOUS, newUSEO,
    //     //                              newCornPerm, newEdgePerm, newUdSliceSorted, newCPEP, newCPUS, newUSEP,
    //     //                              phase, newDepht + 3, newPath );
    //     // }
    //     std::vector<int> newPath = current.path;
    //     newPath.push_back(i);

    //     bestStates.emplace_back( current.cornOrient, current.flipUdSlice, current.P1Depht,
    //                               newCornPerm, newEdgePerm, newUdSliceSorted,
    //                                 phase, newDepht + 3, 0, 0, newPath );

    //     ++moveId;
    // }

    // for (const State& s: bestStates)
    // {
    //     newIndex = hashPath(s.path);
    //     if (close.find( newIndex ) == close.end())
    //     {
    //         close.insert( newIndex );
    //         open.emplace( s );
    //     }
    // }
}


void    Kociemba::solveP1(Cube& rubik)
{

    std::priority_queue<State>  open;
    std::unordered_set<size_t>  close;

    unsigned int cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    unsigned int flipUdSlice =  edgeOrientationCoordinates(rubik.m_edges.o) * UD_SLICE_MOVETABLE_SIZE + UDSliceCoordinates(rubik.m_edges.p);

    unsigned int cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    unsigned int edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    unsigned int udSliceSorted = UDSliceSortedCoordinates(rubik.m_edges.p);

    short phase(1);
    if (cornOrient == 0 && flipUdSlice == 0)
        phase = 2;


    printf("HEY\n");
    open.emplace(
        cornOrient,
        flipUdSlice,
        getValue_P1_PruneTable(FlipUdSlice_Sym[flipUdSlice].first * CORNER_ORIENTATION_MOVETABLE_SIZE
                                + CornOrientSym_MoveTable[cornOrient][FlipUdSlice_Sym[flipUdSlice].second[0]]),
        cornPerm,
        edgePerm,
        udSliceSorted,
        getValue_P2_PruneTable(CornPerm_Sym[cornPerm].first * P2_EDGE_PERMUTATION_MOVETABLE_SIZE
                                + P2EdgePermSym_MoveTable[edgePerm][CornPerm_Sym[cornPerm].second[0]]),
        phase, 0
    );
    printf("HEY\n");
    close.emplace( hashPath(open.top().path) );

    size_t  opened = 0;

    while (!open.empty())
    {
        State current = open.top();
        open.pop();

        /* ===== DEBUG ===== */

        printf("%s %d :: %2d - ( %5u %5u | %5u %5u %5u ) [%2lu]%s ", (current.phase == 1) ? RED : GREEN, current.phase, current.depht, current.cornOrient, current.flipUdSlice, current.cornPerm, current.edgePerm, current.udSliceSorted, current.path.size(), RESET);
        for (auto it = current.path.begin(); it != current.path.end(); ++it)
        {
            std::printf("%s ", moveP1(*it).c_str());
        }
        std::printf("\n");
        
        opened++;

        /* ===== SOLVED ===== */

        if (current.phase == 2 && current.cornPerm == 0 && current.edgePerm == 0 && current.udSliceSorted == 0)
        {
            solveSucess(rubik, current, opened);
            return ;
        }

        /* ===== GENERATE ===== */

        else if (current.phase == 1)
            generateP1(open, close, current, rubik);
        else
            generateP1(open, close, current, rubik);

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