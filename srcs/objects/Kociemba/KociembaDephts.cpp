#include "Kociemba.hpp"

struct State {
    unsigned int    coord;
    unsigned int    depht;

    State(unsigned int c = 0, unsigned int d = 0) 
        : coord(c), depht(d) {} 
};

void    Kociemba::generate_moveTableDepth(std::vector< std::pair<std::vector<unsigned int>, unsigned int> >& moveTable, int nbrMove)
{
    std::queue<State>     Q;

    size_t          size(0);
    size_t          lastSize(0);
    unsigned int    lastDepht(0);

    bool first = true;

    Q.emplace(0,0);

    while (!Q.empty())
    {
        State current = Q.front();
        Q.pop();

        if (current.depht != lastDepht)
        {
            lib::printendl(lastDepht, " :: ", size - lastSize);
            lastDepht = current.depht;
            lastSize = size;
        }

        if (first || (!moveTable[current.coord].second && current.coord))
        {
            first = false;
            moveTable[current.coord].second = current.depht;
            // GENERATE CHILDS
            for (int i = 0; i < nbrMove; ++i)
                Q.emplace(
                    moveTable[current.coord].first[i],
                    current.depht + 1
                );
            ++size;
        }
    }
    lib::printendl("SIZE : ", size);
}

int     Kociemba::generate_Dephts()
{
    generate_moveTableDepth(CornerPermutation_MoveTable, P2_NBR_MOVE);
    generate_moveTableDepth(P2EdgePermutation_MoveTable, P2_NBR_MOVE);
    return (0);
}