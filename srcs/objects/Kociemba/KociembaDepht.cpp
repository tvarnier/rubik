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

unsigned int    Kociemba::getValue_CornPerm_MoveTable(unsigned int index, unsigned int move) { return (CornerPermutation_MoveTable[index][move]); }
void            Kociemba::setValue_CornPerm_DephtTable(unsigned int index, unsigned int depht) { CornerPermutation_DephtTable[index] = depht; }
unsigned int    Kociemba::getValue_CornPerm_DephtTable(unsigned int index) { return (CornerPermutation_DephtTable[index]); }

void    Kociemba::generate_DephtTable(
    unsigned int (*getValue_moveTable)(unsigned int index, unsigned int move),
    void         (*setValue_dephtTable)(unsigned int index, unsigned int depht),
    unsigned int (*getValue_dephtTable)(unsigned int index)
)
{
    std::priority_queue<StateDepht>    Q;
    bool first(true);
    unsigned int                    newCoord;

    Q.emplace(0, 0);
    (*setValue_dephtTable)(0, 0);

    while (!Q.empty())
    {
        StateDepht current = Q.top();
        Q.pop();

        for (unsigned int i = 0; i < 18; ++i)
        {
            newCoord = (*getValue_moveTable)(current.coord, i);
            if (first || ((*getValue_dephtTable)(newCoord) == 0 && newCoord != 0))
            {
                if (!first)
                    (*setValue_dephtTable)(newCoord, current.depht + 1);
                else
                    first = false;
                Q.emplace(newCoord, current.depht + 1);
            }
        }
    }
}

void    Kociemba::generate_dephtTables()
{
    generate_DephtTable(
        &Kociemba::getValue_CornPerm_MoveTable,
        &Kociemba::setValue_CornPerm_DephtTable,
        &Kociemba::getValue_CornPerm_DephtTable
    );
}