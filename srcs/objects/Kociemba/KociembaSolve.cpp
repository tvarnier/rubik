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

struct State {
    unsigned int        cornOrient;
    unsigned int        edgeOrient;
    unsigned int        udSlice;
    uint8_t             COEO;
    uint8_t             COUS;
    uint8_t             USEO;

    unsigned int        cornPerm;
    unsigned int        edgePerm;
    unsigned int        udSliceSorted;
    uint8_t             CPEP;
    uint8_t             CPUS;
    uint8_t             USEP;

    short               phase;
    int                 depht;
    std::vector<int>    path;

    State(unsigned int co = 0, unsigned int eo = 0, unsigned int us = 0,
            uint8_t coeo = 0, uint8_t cous = 0, uint8_t useo = 0,
            unsigned int cp = 0, unsigned int ep = 0, unsigned int uss = 0,
            uint8_t cpep = 0, uint8_t cpus = 0, uint8_t usep = 0,
            short ph = 1, int d = 0, const std::vector<int>& p = std::vector<int>())
    : cornOrient(co), edgeOrient(eo), udSlice(us), COEO(coeo), COUS(cous), USEO(useo),
      cornPerm(cp), edgePerm(ep), udSliceSorted(uss), CPEP(cpep), CPUS(cpus), USEP(usep),
      phase(ph), depht(d), path(p) {}

    bool operator<(const State& other) const { return ((depht == other.depht) ? path.size() > other.path.size() : depht > other.depht); }
    bool operator==(const State& other) const { return (path == other.path); }
};

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

unsigned long long  closeIndex(unsigned int moveId, unsigned int cornOrient, unsigned int edgeOrient, unsigned int udSlice, unsigned int cornPerm, unsigned int edgePerm, unsigned int udSliceSorted)
{
    return (
        cornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE * UD_SLICE_MOVETABLE_SIZE * CORNER_PERMUTATION_MOVETABLE_SIZE * P2_EDGE_PERMUTATION_MOVETABLE_SIZE * UD_SLICE_SORTED_MOVETABLE_SIZE * 18
        + edgeOrient * UD_SLICE_MOVETABLE_SIZE * CORNER_PERMUTATION_MOVETABLE_SIZE * P2_EDGE_PERMUTATION_MOVETABLE_SIZE * UD_SLICE_SORTED_MOVETABLE_SIZE * 18
        + udSlice * CORNER_PERMUTATION_MOVETABLE_SIZE * P2_EDGE_PERMUTATION_MOVETABLE_SIZE * UD_SLICE_SORTED_MOVETABLE_SIZE * 18
        + cornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE * UD_SLICE_SORTED_MOVETABLE_SIZE * 18
        + edgePerm * UD_SLICE_SORTED_MOVETABLE_SIZE * 18
        + udSliceSorted * 18
        + moveId
    );
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
        cornOrient,
        edgeOrient,
        udSlice,
        getValue_P2_CPEP_PruneTable(cornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + edgePerm),
        getValue_P2_CPUS_PruneTable(cornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + udSliceSorted),
        getValue_P2_USEP_PruneTable(udSliceSorted * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + edgePerm),
        phase
    );
    close.emplace( hashPath(open.top().path) );

    size_t  opened = 0;

    while (!open.empty())
    {
        State current = open.top();
        open.pop();

        
        // printf("%s %d :: %d - ( %u %u %u | %u %u %u ) [%d]%s ", (current.phase == 1) ? RED : GREEN, current.phase, current.depht, current.cornOrient, current.edgeOrient, current.udSlice, current.cornPerm, current.edgePerm, current.udSliceSorted, current.path.size(), RESET);
        // for (auto it = current.path.begin(); it != current.path.end(); ++it)
        // {
        //     std::printf("%s ", moveP1(*it).c_str());
        // }
        // std::printf("\n");
        
        opened++;

        if (current.phase == 2 && current.cornPerm == 0 && current.edgePerm == 0 && current.udSliceSorted == 0)
        {
            std::printf("\n Opened = %zu | %lu : ", opened, current.path.size());
            for (auto it = current.path.begin(); it != current.path.end(); ++it)
            {
                std::printf("%s ", moveP1(*it).c_str());
                rubik.move(moveP1(*it).c_str());
            }
            std::printf("\n");
            return ;
        }
        else
        {
            int moveId = 0;
            for (int i = 0; i < 18; ++i)
            {
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
                size_t       newIndex = 0;
                phase = current.phase;

                if (current.phase == 1)
                {
                    newCornOrient  = CornerOrientation_MoveTable[current.cornOrient][i];
                    newEdgeOrient  = EdgeOrientation_MoveTable[current.edgeOrient][i];
                    newUdSlice     = UdSlice_MoveTable[current.udSlice][i];
                    newCOEO  = getValue_P1_COEO_PruneTable(newCornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE + newEdgeOrient);
                    newCOUS  = getValue_P1_COUS_PruneTable(newCornOrient * UD_SLICE_MOVETABLE_SIZE + newUdSlice);
                    newUSEO  = getValue_P1_USEO_PruneTable(newUdSlice * EDGE_ORIENTATION_MOVETABLE_SIZE + newEdgeOrient);

                    newDepht = current.depht + (pruneDiff(current.COEO, newCOEO) + pruneDiff(current.COUS, newCOUS) + pruneDiff(current.USEO, newUSEO));

                    if (newCornOrient == 0 && newEdgeOrient == 0 && newUdSlice == 0)
                    {
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
                        newCPEP = getValue_P2_CPEP_PruneTable(newCornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
                        newCPUS = getValue_P2_CPUS_PruneTable(newCornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + newUdSliceSorted);
                        newUSEP = getValue_P2_USEP_PruneTable(newUdSliceSorted * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);

                        
                    }
                }
                else if (current.phase == 2)
                {
                    if ((i / 3 == 1 || i / 3 == 2 || i / 3 == 4 || i / 3 == 5)
                        && (i % 3 == 0 || i % 3 == 2))
                        continue ;
                    newCornPerm        = CornerPermutation_MoveTable[current.cornPerm][moveId];
                    newEdgePerm        = P2EdgePermutation_MoveTable[current.edgePerm][moveId];
                    newUdSliceSorted   = UdSliceSorted_MoveTable[current.udSliceSorted][moveId];
                    newCPEP  = getValue_P2_CPEP_PruneTable(newCornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
                    newCPUS  = getValue_P2_CPUS_PruneTable(newCornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + newUdSlice);
                    newUSEP  = getValue_P2_USEP_PruneTable(newUdSliceSorted * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
                
                    newDepht = current.depht + (pruneDiff(current.CPEP, newCPEP) + pruneDiff(current.CPUS, newCPUS) + pruneDiff(current.USEP, newUSEP));
                }


                std::vector<int> newPath = current.path;
                newPath.push_back(i);
                newIndex = hashPath(newPath);
                
                if (close.find( newIndex ) == close.end())
                {
                    close.insert( newIndex );
                    open.emplace(newCornOrient, newEdgeOrient, newUdSlice, newCOEO, newCOUS, newUSEO,
                                    newCornPerm, newEdgePerm, newUdSliceSorted, newCPEP, newCPUS, newUSEP,
                                    phase, newDepht + 3, newPath);
                }
                ++moveId;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*struct StateP2 {
    unsigned int        cornPerm;
    unsigned int        edgePerm;
    unsigned int        udSlice;
    int                 depht;
    uint8_t             CPEP;
    uint8_t             CPUS;
    uint8_t             USEP;
    std::vector<int>    path;

    StateP2(unsigned int cp = 0, unsigned int ep = 0, unsigned int us = 0, int d = 0, uint8_t cpep = 0, uint8_t cpus = 0, uint8_t usep = 0, const std::vector<int>& p = std::vector<int>())
    : cornPerm(cp), edgePerm(ep), udSlice(us), depht(d), CPEP(cpep), CPUS(cpus), USEP(usep), path(p) {}

    bool operator<(const StateP2& other) const { return (depht > other.depht); }
    bool operator==(const StateP2& other) const { return (cornPerm == other.cornPerm && edgePerm == other.edgePerm && udSlice == other.udSlice); }
};

std::string moveP2(int i)
{
    std::string moves[10] = {
        "U", "U2", "U'", "R2", "F2", "D", "D2", "D'", "L2", "B2"
    };
    return (moves[i]);
}

void    Kociemba::solveP2(Cube& rubik)
{
    std::priority_queue<StateP2>            open;
    std::unordered_set<unsigned long long>  close;

    unsigned int cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    unsigned int edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    unsigned int udSlice = UDSliceSortedCoordinates(rubik.m_edges.p);

    open.emplace(
        cornPerm,
        edgePerm,
        udSlice,
        0,
        getValue_P2_CPEP_PruneTable(cornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + edgePerm),
        getValue_P2_CPUS_PruneTable(cornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + udSlice),
        getValue_P2_USEP_PruneTable(udSlice * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + edgePerm)
    );
    close.emplace(open.top().cornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE * UD_SLICE_SORTED_MOVETABLE_SIZE + open.top().edgePerm * UD_SLICE_SORTED_MOVETABLE_SIZE + open.top().udSlice);

    while (!open.empty())
    {
        StateP2 current = open.top();
        open.pop();

        if (current.cornPerm == 0 && current.edgePerm == 0 && current.udSlice == 0)
        {
            std::printf("\n%lu : ", current.path.size());
            for (auto it = current.path.begin(); it != current.path.end(); ++it)
            {
                std::printf("%s ", moveP2(*it).c_str());
                rubik.move(moveP2(*it).c_str());
            }
            std::printf("\n");
            return ;
        }
        else
        {
            for (int i = 0; i < P2_NBR_MOVE; ++i)
            {
                unsigned int newCornPerm    = CornerPermutation_MoveTable[current.cornPerm][i];
                unsigned int newEdgePerm    = P2EdgePermutation_MoveTable[current.edgePerm][i];
                unsigned int newUdSlice     = UdSliceSorted_MoveTable[current.udSlice][i];
                uint8_t      newCPEP  = getValue_P2_CPEP_PruneTable(newCornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);
                uint8_t      newCPUS  = getValue_P2_CPUS_PruneTable(newCornPerm * UD_SLICE_SORTED_MOVETABLE_SIZE + newUdSlice);
                uint8_t      newUSEP  = getValue_P2_USEP_PruneTable(newUdSlice * P2_EDGE_PERMUTATION_MOVETABLE_SIZE + newEdgePerm);

                int          newDepht       = current.depht + pruneDiff(current.CPEP, newCPEP) + pruneDiff(current.CPUS, newCPUS) + pruneDiff(current.USEP, newUSEP);
                
                if (close.find(newCornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE * UD_SLICE_SORTED_MOVETABLE_SIZE + newEdgePerm * UD_SLICE_SORTED_MOVETABLE_SIZE + newUdSlice) == close.end())
                {
                    close.insert(newCornPerm * P2_EDGE_PERMUTATION_MOVETABLE_SIZE * UD_SLICE_SORTED_MOVETABLE_SIZE + newEdgePerm * UD_SLICE_SORTED_MOVETABLE_SIZE + newUdSlice);
                    std::vector<int> newPath = current.path;
                    newPath.push_back(i);
                    open.emplace(newCornPerm, newEdgePerm, newUdSlice, newDepht + 3, newCPEP, newCPUS, newUSEP, newPath);
                }
            }
        }
    }
}*/

void    Kociemba::solve(Cube rubik)
{
    // for (int i = 0; i < 18; i++)
    // {
    //     printf("   %d -> %u | %u | %u\n", i,  CornerOrientation_MoveTable[137][i], EdgeOrientation_MoveTable[137][i], UdSlice_MoveTable[288][i]);
    // }

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

    // solveP2(rubik);

    // cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    // edgeOrient = edgeOrientationCoordinates(rubik.m_edges.o);
    // udSlice = UDSliceCoordinates(rubik.m_edges.p);
    // cornPerm = cornerPermutationCoordinates(rubik.m_corners.p);
    // edgePerm = phase2EdgePermutationCoordinates(rubik.m_edges.p);
    // udSliceS = UDSliceSortedCoordinates(rubik.m_edges.p);

    // std::printf("CORNER ORIENTATION     : %u\n", cornOrient);
    // std::printf("EDGE ORIENTATION       : %u\n", edgeOrient);
    // std::printf("UD SLICE               : %u\n", udSlice);
    // std::printf("CORNER PERMUTATION     : %u\n", cornPerm);
    // std::printf("EDGE ORIENTATION       : %u\n", edgePerm);
    // std::printf("UD SLICE SORTED        : %u\n", udSliceS);
}