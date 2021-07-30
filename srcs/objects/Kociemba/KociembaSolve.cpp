#include "Kociemba.hpp"

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

int     pruneDiff(uint8_t currentDepht, uint8_t newDepht)
{
    if (currentDepht == 1 && newDepht == 3)
        return -1;
    else if (currentDepht == 3 && newDepht == 1)
        return +1;
    else
        return (newDepht - currentDepht);
}

void    Kociemba::solveP2(Cube rubik)
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
                std::printf("%s ", moveP2(*it).c_str());
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
    solveP2(rubik);
}