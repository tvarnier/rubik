#include "Kociemba.hpp"

int     pruneDiff(uint8_t currentDepht, uint8_t newDepht)
{
    if (currentDepht == 1 && newDepht == 3)
        return -1;
    else if (currentDepht == 3 && newDepht == 1)
        return +1;
    else
        return (newDepht - currentDepht);
}

struct StateP1 {
    unsigned int        cornOrient;
    unsigned int        edgeOrient;
    unsigned int        udSlice;
    int                 depht;
    uint8_t             COEO;
    uint8_t             COUS;
    uint8_t             USEO;
    std::vector<int>    path;

    StateP1(unsigned int co = 0, unsigned int eo = 0, unsigned int us = 0, int d = 0, uint8_t coeo = 0, uint8_t cous = 0, uint8_t useo = 0, const std::vector<int>& p = std::vector<int>())
    : cornOrient(co), edgeOrient(eo), udSlice(us), depht(d), COEO(coeo), COUS(cous), USEO(useo), path(p) {}

    bool operator<(const StateP1& other) const { return (depht > other.depht); }
    bool operator==(const StateP1& other) const { return (cornOrient == other.cornOrient && edgeOrient == other.edgeOrient && udSlice == other.udSlice); }
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

void    Kociemba::solveP1(Cube& rubik)
{
    std::priority_queue<StateP1>            open;
    std::unordered_set<unsigned long long>  close;

    unsigned int cornOrient = cornerOrientationCoordinates(rubik.m_corners.o);
    unsigned int edgeOrient = edgeOrientationCoordinates(rubik.m_edges.o);
    unsigned int udSlice = UDSliceCoordinates(rubik.m_edges.p);

    open.emplace(
        cornOrient,
        edgeOrient,
        udSlice,
        0,
        getValue_P1_COEO_PruneTable(cornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE + edgeOrient),
        getValue_P1_COUS_PruneTable(cornOrient * UD_SLICE_MOVETABLE_SIZE + udSlice),
        getValue_P1_USEO_PruneTable(udSlice * EDGE_ORIENTATION_MOVETABLE_SIZE + edgeOrient)
    );
    close.emplace(open.top().cornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE * UD_SLICE_MOVETABLE_SIZE + open.top().edgeOrient * UD_SLICE_MOVETABLE_SIZE + open.top().udSlice);

    while (!open.empty())
    {
        StateP1 current = open.top();
        open.pop();

        if (current.cornOrient == 0 && current.edgeOrient == 0 && current.udSlice == 0)
        {
            std::printf("\n%lu : ", current.path.size());
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
            for (int i = 0; i < P1_NBR_MOVE; ++i)
            {
                unsigned int newCornOrient  = CornerOrientation_MoveTable[current.cornOrient][i];
                unsigned int newEdgeOrient  = EdgeOrientation_MoveTable[current.edgeOrient][i];
                unsigned int newUdSlice     = UdSlice_MoveTable[current.udSlice][i];
                uint8_t      newCOEO  = getValue_P1_COEO_PruneTable(newCornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE + newEdgeOrient);
                uint8_t      newCOUS  = getValue_P1_COUS_PruneTable(newCornOrient * UD_SLICE_MOVETABLE_SIZE + newUdSlice);
                uint8_t      newUSEO  = getValue_P1_USEO_PruneTable(newUdSlice * EDGE_ORIENTATION_MOVETABLE_SIZE + newEdgeOrient);

                int          newDepht   = current.depht + pruneDiff(current.COEO, newCOEO) + pruneDiff(current.COUS, newCOUS) + pruneDiff(current.USEO, newUSEO);
                
                if (close.find(newCornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE * UD_SLICE_MOVETABLE_SIZE + newEdgeOrient * UD_SLICE_MOVETABLE_SIZE + newUdSlice) == close.end())
                {
                    close.insert(newCornOrient * EDGE_ORIENTATION_MOVETABLE_SIZE * UD_SLICE_MOVETABLE_SIZE + newEdgeOrient * UD_SLICE_MOVETABLE_SIZE + newUdSlice);
                    std::vector<int> newPath = current.path;
                    newPath.push_back(i);
                    open.emplace(newCornOrient, newEdgeOrient, newUdSlice, newDepht + 3, newCOEO, newCOUS, newUSEO, newPath);
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct StateP2 {
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
}

void    Kociemba::solve(Cube rubik)
{
    solveP1(rubik);

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

    solveP2(rubik);

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