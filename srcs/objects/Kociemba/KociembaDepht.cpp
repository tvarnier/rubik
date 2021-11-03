#include "Kociemba.hpp"

struct StateDepht {
    unsigned int    coord;
    unsigned int    depht;

    StateDepht(unsigned int c = 0, unsigned int d = 0)
    : coord(c), depht(d) {}

    bool operator<(const StateDepht& other) const
    {
        return depht > other.depht;
    }
};

void    Kociemba::DephtTable::Generate::one(
    std::vector< unsigned int >& dephtTable,
    const std::vector< std::array<unsigned int, 18> >& moveTable,
    int nbrMoves
)
{
    std::priority_queue<StateDepht>    Q;
    bool first(true);
    unsigned int                    newCoord;

    Q.emplace(0, 0);
    dephtTable[0] = 0;

    while (!Q.empty())
    {
        StateDepht current = Q.top();
        Q.pop();

        for (unsigned int i = 0; i < nbrMoves; ++i)
        {
            newCoord = moveTable[current.coord][i];
            if (first || (dephtTable[newCoord] == 0 && newCoord != 0))
            {
                if (!first)
                    dephtTable[newCoord] = current.depht + 1;
                else
                    first = false;
                Q.emplace(newCoord, current.depht + 1);
            }
        }
    }
}