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

unsigned int    Kociemba::getValue_EdgePerm_MoveTable(unsigned int index, unsigned int move){ return (P2EdgePermutation_MoveTable[index][move]); }
void            Kociemba::setValue_EdgePerm_DephtTable(unsigned int index, unsigned int depht) { EdgePermutation_DephtTable[index] = depht; }
unsigned int    Kociemba::getValue_EdgePerm_DephtTable(unsigned int index) { return (EdgePermutation_DephtTable[index]); }

unsigned int    Kociemba::getValue_UdSliceSorted_MoveTable(unsigned int index, unsigned int move){ return (UdSliceSorted_MoveTable[index][move]); }
void            Kociemba::setValue_UdSliceSorted_DephtTable(unsigned int index, unsigned int depht) { UdSliceSorted_DephtTable[index] = depht; }
unsigned int    Kociemba::getValue_UdSliceSorted_DephtTable(unsigned int index) { return (UdSliceSorted_DephtTable[index]); }

void    Kociemba::generate_DephtTable(
    unsigned int (Kociemba::*getValue_moveTable)(unsigned int index, unsigned int move),
    void         (Kociemba::*setValue_dephtTable)(unsigned int index, unsigned int depht),
    unsigned int (Kociemba::*getValue_dephtTable)(unsigned int index)
)
{
    std::priority_queue<StateDepht>    Q;
    bool first(true);
    unsigned int                    newCoord;

    Q.emplace(0, 0);
    (this->*setValue_dephtTable)(0, 0);

    while (!Q.empty())
    {
        StateDepht current = Q.top();
        Q.pop();

        for (unsigned int i = 0; i < 18; ++i)
        {
            if ((i / 3 == UP || i / 3 == DOWN)
                || (i % 3 == 1))
            {
                newCoord = (this->*getValue_moveTable)(current.coord, i);
                if (first || ((this->*getValue_dephtTable)(newCoord) == 0 && newCoord != 0))
                {
                    if (!first)
                        (this->*setValue_dephtTable)(newCoord, current.depht + 1);
                    else
                        first = false;
                    Q.emplace(newCoord, current.depht + 1);
                }
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
    generate_DephtTable(
        &Kociemba::getValue_EdgePerm_MoveTable,
        &Kociemba::setValue_EdgePerm_DephtTable,
        &Kociemba::getValue_EdgePerm_DephtTable
    );
    generate_DephtTable(
        &Kociemba::getValue_UdSliceSorted_MoveTable,
        &Kociemba::setValue_UdSliceSorted_DephtTable,
        &Kociemba::getValue_UdSliceSorted_DephtTable
    );
}