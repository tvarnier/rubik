#include "Kociemba.hpp"

struct StateSolver {
    unsigned int        cornPerm;
    unsigned int        edgePerm;
    unsigned int        depht;
    unsigned int        score;
    std::vector<int>    way;

    StateSolver(unsigned int cP = 0, unsigned int eP = 0, unsigned int d = 0, unsigned s = 0, std::vector<int> w = std::vector<int>()) 
        : cornPerm(cP), edgePerm(eP), depht(d), score(s), way(w) {}

    bool operator<(const StateSolver& other) const
    {
        return score > other.score;
    }
};

std::string     P2Moves(int& i)
{
    std::array<std::string, 10> t = { "U","U'","U2","R2","F2","D","D'","D2","L2","B2" };
    return (t[i]);
}

bool    done[40320 * 40320];

int     Kociemba::solveP2(Cube rubik)
{
    std::priority_queue<StateSolver>    Q;

    for (int i = 0; i < 40320 * 40320; ++i)
        done[i] = false;

    size_t size(0);

    std::vector<int>    newWay(0);

    Q.emplace(
        cornerPermutationCoordinates(rubik.m_corners.p),
        phase2EdgePermutationCoordinates(rubik.m_edges.p),
        0 , 0, newWay
    );
    while (!Q.empty())
    {
        StateSolver   current = Q.top();
        Q.pop();
        if (!current.cornPerm && !current.edgePerm)
        {
            lib::printendl("SOLVED : ", current.depht);
            for (auto i = current.way.begin(); i != current.way.end(); ++i)
            {
                std::printf("%s\n", P2Moves(*i).c_str());
            }
            break ;
        }

        ++size;
        /*if (size % 1 == 0)
            std::printf("% 8u : % 2u\n", size, current.score);*/

        if (current.depht < 18 && !done[current.cornPerm * 40320 + current.edgePerm])
        {
            done[current.cornPerm * 40320 + current.edgePerm] = true;
            for (int i = 0; i < 10; ++i)
            {
                unsigned int newCornPerm = CornerPermutation_MoveTable[current.cornPerm].first[i];
                unsigned int newEdgePerm = P2EdgePermutation_MoveTable[current.edgePerm].first[i];
                newWay = current.way;
                newWay.push_back(i);
                Q.emplace(
                    newCornPerm,
                    newEdgePerm,
                    current.depht + 1,
                    (CornerPermutation_MoveTable[newCornPerm].second + P2EdgePermutation_MoveTable[newEdgePerm].second) + (current.depht + 1) * 2,
                    newWay
                );
            }
        }

    }
    return (0);
}

int     Kociemba::solve(Cube rubik)
{
    solveP2(rubik);
    return (0);
}