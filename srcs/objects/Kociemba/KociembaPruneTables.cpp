#include "Kociemba.hpp"

/* ============================  P1  ============================ */

char    Kociemba::getValue_P1_PruneTable(unsigned long long index) { return ( (Kociemba::P1_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::setValue_P1_PruneTable(unsigned long long index, char value) { Kociemba::P1_PruneTable[index / 4] =  Kociemba::P1_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }

/* ============================ CPEP ============================ */

char    Kociemba::getValue_P2_CPEP_PruneTable(unsigned long long index) { return ( (Kociemba::P2_CPEP_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::setValue_P2_CPEP_PruneTable(unsigned long long index, char value) { Kociemba::P2_CPEP_PruneTable[index / 4] =  Kociemba::P2_CPEP_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }


/* ============================ ---- ============================ */

struct StatePruning {
    unsigned int    coord1;
    unsigned int    coord2;
    unsigned int    depht;

    StatePruning(unsigned int c1 = 0, unsigned int c2 = 0, unsigned int d = 0)
    : coord1(c1), coord2(c2), depht(d) {}

    bool operator<(const StatePruning& other) const
    {
        return depht > other.depht;
    }
};

void    Kociemba::generatePruneTable_P1()
{
    std::priority_queue<StatePruning>    Q;
    unsigned int                    newCoord1;
    unsigned int                    newCoord2;

    unsigned long long              newIndex;

    unsigned long long              size(1);
    unsigned long long              lastSize(1);
    unsigned int                    lastDepht(0);

    Q.emplace(0, 0, 0);
    setValue_P1_PruneTable(0, 1);

    while (!Q.empty())
    {
        for (unsigned int i = 0; i < 18; ++i)
        {
            if (Q.top().depht != lastDepht)
            {
                std::printf("Depht : %u - %llu\n", Q.top().depht, size - lastSize);
                lastSize = size;
                lastDepht = Q.top().depht;
            }

            newCoord1 = CornerOrientation_MoveTable[Q.top().coord1][i];
            newCoord2 = FlipUDSlice_MoveTable[Q.top().coord2][i];
            unsigned int rep = FlipUDSlice_Sym[newCoord2].first;

            for (auto sym : FlipUDSlice_Sym[newCoord2].second)
            {
                unsigned int newCornOrient = Kociemba::CornOrientSym_MoveTable[newCoord1][sym];
                newIndex = rep * 2187 + newCornOrient;
                if (getValue_P1_PruneTable(newIndex) == 0)
                {
                    setValue_P1_PruneTable(newIndex, ((Q.top().depht + 1) % 3) + 1);
                    Q.emplace(newCornOrient, FlipUDSlice_SymRep[rep], Q.top().depht + 1);
                    ++size;
                }
            }
        }
        Q.pop();
    }
}

void    Kociemba::generatePruneTable_P2()
{
    std::priority_queue<StatePruning>    Q;
    unsigned int                    newCoord1;
    unsigned int                    newCoord2;

    unsigned long long              newIndex;

    unsigned long long              size(1);
    unsigned long long              lastSize(1);
    unsigned int                    lastDepht(0);

    Q.emplace(0, 0, 0);
    setValue_P2_CPEP_PruneTable(0, 1);

    while (!Q.empty())
    {
        for (unsigned int i = 0; i < 18; ++i)
        {
            if ((i / 3 == ROT_UP || i / 3 == ROT_DOWN)
                    || (i % 3 == 1))
            {
                if (Q.top().depht != lastDepht)
                {
                    std::printf("Depht : %u - %llu\n", Q.top().depht, size - lastSize);
                    lastSize = size;
                    lastDepht = Q.top().depht;
                }

                newCoord1 = CornerPermutation_MoveTable[Q.top().coord1][i];
                newCoord2 = P2EdgePermutation_MoveTable[Q.top().coord2][i];
                unsigned int rep = CornPerm_Sym[newCoord1].first;

                for (auto sym : CornPerm_Sym[newCoord1].second)
                {
                    unsigned int newEdgeSym = Kociemba::P2EdgePermSym_MoveTable[newCoord2][sym]; 
                    newIndex = newEdgeSym * 2768 + rep;
                    if (getValue_P2_CPEP_PruneTable(newIndex) == 0)
                    {
                        setValue_P2_CPEP_PruneTable(newIndex, ((Q.top().depht + 1) % 3) + 1);
                        Q.emplace(CornPerm_SymRep[rep], newEdgeSym, Q.top().depht + 1);
                        ++size;
                    }
                }
            }
        }
        Q.pop();
    }
}

void    Kociemba::generate_pruneTables()
{
    std::ifstream fileP1;
    fileP1.open(std::string("./data/P1").c_str());
    if (fileP1)
    {
        fileP1.seekg(0, std::ios::end);
        size_t length = fileP1.tellg();
        fileP1.seekg(0, std::ios::beg);
        if (length > 554273280)
        {
            length = 554273280;
        }
        fileP1.read(P1_PruneTable, length);
    }
    else
    {
        generatePruneTable_P1();

        FILE *file = fopen(std::string("./data/P1").c_str(), "w");
        int results = fputs(P1_PruneTable, file);
        if (results == EOF) {
            std::printf("FAIL TO WRITE\n");
        }
        fclose(file);
    }



    std::ifstream fileP2;
    fileP2.open(std::string("./data/P2_CPEP").c_str());
    if (fileP2)
    {
        fileP2.seekg(0, std::ios::end);
        size_t length = fileP2.tellg();
        fileP2.seekg(0, std::ios::beg);
        if (length > 27901440)
        {
            length = 27901440;
        }
        fileP2.read(P2_CPEP_PruneTable, length);
    }
    else
    {
        generatePruneTable_P2();

        FILE *file = fopen(std::string("./data/P2_CPEP").c_str(), "w");
        int results = fputs(P2_CPEP_PruneTable, file);
        if (results == EOF) {
            std::printf("FAIL TO WRITE\n");
        }
        fclose(file);
    }
}