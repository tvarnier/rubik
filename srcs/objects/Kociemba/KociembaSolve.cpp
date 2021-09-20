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
        unsigned int newCornOrient  = current.cornOrient;
        unsigned int newEdgeOrient  = current.edgeOrient;
        unsigned int newUdSlice     = current.udSlice;
        uint8_t      newCOEO  = current.COEO;
        uint8_t      newCOUS  = current.COUS;
        uint8_t      newUSEO  = current.USEO;

        uint8_t     newP1Depht = current.P1Depht;

        unsigned int newCornPerm  = current.cornPerm;
        unsigned int newEdgePerm  = current.edgePerm;
        unsigned int newUdSliceSorted   = current.udSliceSorted;
        uint8_t      newCPEP  = current.CPEP;
        uint8_t      newCPUS  = current.CPUS;
        uint8_t      newUSEP  = current.USEP;

        int          newDepht = current.depht;
        size_t       newIndex = 0;
        short        phase = current.phase;

        newCornOrient  = CornerOrientation_MoveTable[current.cornOrient][i];
        newEdgeOrient  = EdgeOrientation_MoveTable[current.edgeOrient][i];
        newUdSlice     = UdSlice_MoveTable[current.udSlice][i];
        newP1Depht = getValue_P1_PruneTable(newCornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE * UD_SLICE_MOVETABLE_SIZE + newEdgeOrient * UD_SLICE_MOVETABLE_SIZE + newUdSlice);
        newCOEO  = getValue_P1_COEO_PruneTable(newCornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE + newEdgeOrient);
        newCOUS  = getValue_P1_COUS_PruneTable(newCornOrient * UD_SLICE_MOVETABLE_SIZE + newUdSlice);
        newUSEO  = getValue_P1_USEO_PruneTable(newUdSlice * EDGE_ORIENTATION_MOVETABLE_SIZE + newEdgeOrient);

        if ((i / 3 == UP || i / 3 == DOWN)
            || (i % 3 == 1))
        {
            newCornPerm        = CornerPermutation_MoveTable[current.cornPerm][i];
            newEdgePerm        = P2EdgePermutation_MoveTable[current.edgePerm][i];
            newUdSliceSorted   = UdSliceSorted_MoveTable[current.udSliceSorted][i];
        }
        else
        {
            Cube tmp(rubik);
            for (auto it = current.path.begin(); it != current.path.end(); ++it)
            {
                tmp.move(moveP1(*it).c_str());
            }
            tmp.move(moveP1(i).c_str());
            newCornPerm = cornerPermutationCoordinates(tmp.m_corners.p);
            newEdgePerm = phase2EdgePermutationCoordinates(tmp.m_edges.p);
            newUdSliceSorted = UDSliceSortedCoordinates(tmp.m_edges.p);
        }

        //newDepht = current.depht + (pruneDiff(current.COEO, newCOEO) + pruneDiff(current.COUS, newCOUS) + pruneDiff(current.USEO, newUSEO)) + (Phase2Depht(newCornPerm, newEdgePerm, newUdSliceSorted) - current.P2Depht);
        newDepht = current.depht + (pruneDiff(current.P1Depht, newP1Depht)) * 3 + (Phase2Depht(newCornPerm, newEdgePerm, newUdSliceSorted) - current.P2Depht);

        if (newCornOrient == 0 && newEdgeOrient == 0 && newUdSlice == 0)
        {
            countP2--;
            phase = 2;
            newCPEP = getValue_P2_CPEP_PruneTable(newCornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
            newCPUS = getValue_P2_CPUS_PruneTable(newCornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + newUdSliceSorted);
            newUSEP = getValue_P2_USEP_PruneTable(newUdSliceSorted * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
            // Cube tmp(rubik);
            // for (auto it = current.path.begin(); it != current.path.end(); ++it)
            // {
            //     tmp.move(moveP1(*it).c_str());
            // }
            // tmp.move(moveP1(i).c_str());
            // newCornPerm = cornerPermutationCoordinates(tmp.m_corners.p);
            // newEdgePerm = phase2EdgePermutationCoordinates(tmp.m_edges.p);
            // newUdSliceSorted = UDSliceSortedCoordinates(tmp.m_edges.p);
            // newCPEP = getValue_P2_CPEP_PruneTable(newCornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
            // newCPUS = getValue_P2_CPUS_PruneTable(newCornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + newUdSliceSorted);
            // newUSEP = getValue_P2_USEP_PruneTable(newUdSliceSorted * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
        }

        std::vector<int> newPath = current.path;
        newPath.push_back(i);
        newIndex = hashPath(newPath);
        
        if (close.find( newIndex ) == close.end())
        {
            close.insert( newIndex );
            open.emplace(newCornOrient, newEdgeOrient, newUdSlice, newCOEO, newCOUS, newUSEO,
                            newCornPerm, newEdgePerm, newUdSliceSorted, newCPEP, newCPUS, newUSEP,
                            phase, newDepht + 3, newP1Depht, Phase2Depht(newCornPerm, newEdgePerm, newUdSliceSorted), newPath);
        }
    }
}

void    Kociemba::generateP2(std::priority_queue<State>& open, std::unordered_set<size_t>& close, State& current)
{
    std::vector<State>  bestStates;
    int     minDepht = 2147483647;
    size_t  newIndex = 0;

    int moveId = 0;
    for (int i = 0; i < 18; ++i)
    {
        if ((i / 3 == RIGHT || i / 3 == FRONT || i / 3 == LEFT || i / 3 == BACK)
            && (i % 3 == 0 || i % 3 == 2))
                continue ;
        unsigned int newCornOrient  = current.cornOrient;
        unsigned int newEdgeOrient  = current.edgeOrient;
        unsigned int newUdSlice     = current.udSlice;
        uint8_t      newCOEO  = current.COEO;
        uint8_t      newCOUS  = current.COUS;
        uint8_t      newUSEO  = current.USEO;

        unsigned int newCornPerm  = current.cornPerm;
        unsigned int newEdgePerm  = current.edgePerm;
        unsigned int newUdSliceSorted   = current.udSliceSorted;
        uint8_t      newCPEP  = current.CPEP;
        uint8_t      newCPUS  = current.CPUS;
        uint8_t      newUSEP  = current.USEP;

        int          newDepht = current.depht;
        short        phase = current.phase;

        newCornPerm        = CornerPermutation_MoveTable[current.cornPerm][i];
        newEdgePerm        = P2EdgePermutation_MoveTable[current.edgePerm][i];
        newUdSliceSorted   = UdSliceSorted_MoveTable[current.udSliceSorted][i];
        newCPEP  = getValue_P2_CPEP_PruneTable(newCornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
        newCPUS  = getValue_P2_CPUS_PruneTable(newCornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + newUdSlice);
        newUSEP  = getValue_P2_USEP_PruneTable(newUdSliceSorted * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
    
        int newPruneDiff((pruneDiff(current.CPEP, newCPEP) + pruneDiff(current.CPUS, newCPUS) + pruneDiff(current.USEP, newUSEP)));

        if (newPruneDiff > 0) { newPruneDiff *= 3; }

        newDepht = current.depht + newPruneDiff;

        // if (newDepht < minDepht)
        // {
        //     minDepht = newDepht;
        //     bestStates.clear();
        // }
        // if (newDepht == minDepht)
        // {
        //     std::vector<int> newPath = current.path;
        //     newPath.push_back(i);

        //     bestStates.emplace_back( newCornOrient, newEdgeOrient, newUdSlice, newCOEO, newCOUS, newUSEO,
        //                              newCornPerm, newEdgePerm, newUdSliceSorted, newCPEP, newCPUS, newUSEP,
        //                              phase, newDepht + 3, newPath );
        // }
        std::vector<int> newPath = current.path;
        newPath.push_back(i);

        bestStates.emplace_back( newCornOrient, newEdgeOrient, newUdSlice, newCOEO, newCOUS, newUSEO,
                                    newCornPerm, newEdgePerm, newUdSliceSorted, newCPEP, newCPUS, newUSEP,
                                    phase, newDepht + 3, 0, 0, newPath );

        ++moveId;
    }

    for (const State& s: bestStates)
    {
        newIndex = hashPath(s.path);
        if (close.find( newIndex ) == close.end())
        {
            close.insert( newIndex );
            open.emplace( s );
        }
    }
}


void    Kociemba::solveP1(Cube& rubik)
{

    std::priority_queue<State>  open;
    std::unordered_set<size_t>  close;

    unsigned int cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    unsigned int edgeOrient = edgeOrientationCoordinates(rubik.m_edges.o);
    unsigned int udSlice = UDSliceCoordinates(rubik.m_edges.p);

    unsigned int cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    unsigned int edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    unsigned int udSliceSorted = UDSliceSortedCoordinates(rubik.m_edges.p);

    short phase(1);
    if (cornOrient == 0 && edgeOrient == 0 && udSlice == 0)
        phase = 2;

    open.emplace(
        cornOrient,
        edgeOrient,
        udSlice,
        getValue_P1_COEO_PruneTable(cornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE + edgeOrient),
        getValue_P1_COUS_PruneTable(cornOrient * UD_SLICE_MOVETABLE_SIZE + udSlice),
        getValue_P1_USEO_PruneTable(udSlice * EDGE_ORIENTATION_MOVETABLE_SIZE + edgeOrient),
        cornPerm,
        edgePerm,
        udSliceSorted,
        getValue_P2_CPEP_PruneTable(cornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + edgePerm),
        getValue_P2_CPUS_PruneTable(cornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + udSliceSorted),
        getValue_P2_USEP_PruneTable(udSliceSorted * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + edgePerm),
        phase, 0,
        getValue_P1_PruneTable(cornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE * UD_SLICE_MOVETABLE_SIZE + edgeOrient * UD_SLICE_MOVETABLE_SIZE + udSlice),
        Phase2Depht(cornPerm, edgePerm, udSliceSorted)
    );
    close.emplace( hashPath(open.top().path) );

    size_t  opened = 0;

    while (!open.empty())
    {
        State current = open.top();
        open.pop();

        /* ===== DEBUG ===== */

        printf("%s %d :: %2d - ( %5u %5u %5u | %5u %5u %5u ) [%2lu]%s ", (current.phase == 1) ? RED : GREEN, current.phase, current.depht, current.cornOrient, current.edgeOrient, current.udSlice, current.cornPerm, current.edgePerm, current.udSliceSorted, current.path.size(), RESET);
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
        {   if (countP2) generateP1(open, close, current, rubik); }
        else
            generateP2(open, close, current);

    }
}

void    Kociemba::solve(Cube rubik)
{
    for (int i = 0; i < 18; i++)
    {
        printf("   %d -> %u | %u | %u\n", i,  CornerPermutation_MoveTable[21977][i], P2EdgePermutation_MoveTable[11680][i], UdSliceSorted_MoveTable[1][i]);
    }

    // Cube test;
    // auto orient = test.m_corners.o;
    // for (int i = 0; i < 4; ++i)
    // {
    //     orient = Cube::rotateCornOrient(orient, 1);
    //     printf("R -> [");
        
    //     for (int y = 0; y < 8; ++y)
    //         printf("%u ", orient[y]);
    //     printf("] \n");
    // }

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