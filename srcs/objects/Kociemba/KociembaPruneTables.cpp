#include "Kociemba.hpp"

/* ============================  P1  ============================ */

char    Kociemba::PruneTable::Get::value_P1(unsigned long long index) { return ( (Kociemba::PruneTable::P1[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::PruneTable::Set::value_P1(unsigned long long index, char value) { Kociemba::PruneTable::P1[index / 4] =  Kociemba::PruneTable::P1[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }

/* ============================ CPEP ============================ */

char    Kociemba::PruneTable::Get::value_P2_CPEP(unsigned long long index) { return ( (Kociemba::PruneTable::P2_CPEP[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::PruneTable::Set::value_P2_CPEP(unsigned long long index, char value) { Kociemba::PruneTable::P2_CPEP[index / 4] =  Kociemba::PruneTable::P2_CPEP[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }


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

void    Kociemba::PruneTable::Generate::P1()
{
    std::priority_queue<StatePruning>    Q;
    unsigned int                    newCoord1;
    unsigned int                    newCoord2;

    unsigned long long              newIndex;

    Q.emplace(0, 0, 0);
    PruneTable::Set::value_P1(0, 1);

    while (!Q.empty())
    {
        for (unsigned int i = 0; i < 18; ++i)
        {
            newCoord1 = MoveTable::CornerOrientation[Q.top().coord1][i];
            newCoord2 = MoveTable::FlipUDSlice[Q.top().coord2][i];
            unsigned int rep = Sym::RepTable::FlipUDSlice[newCoord2].first;

            for (auto sym : Sym::RepTable::FlipUDSlice[newCoord2].second)
            {
                unsigned int newCornOrient = Sym::MoveTable::cornerOrientation[newCoord1][sym];
                newIndex = rep * 2187 + newCornOrient;
                if (PruneTable::Get::value_P1(newIndex) == 0)
                {
                    PruneTable::Set::value_P1(newIndex, ((Q.top().depht + 1) % 3) + 1);
                    Q.emplace(newCornOrient, Sym::Rep::FlipUDSlice[rep], Q.top().depht + 1);
                }
            }
        }
        Q.pop();
    }
}

void    Kociemba::PruneTable::Generate::P2_CPEP()
{
    std::priority_queue<StatePruning>    Q;
    unsigned int                    newCoord1;
    unsigned int                    newCoord2;

    unsigned long long              newIndex;

    Q.emplace(0, 0, 0);
    PruneTable::Set::value_P2_CPEP(0, 1);

    while (!Q.empty())
    {
        for (unsigned int i = 0; i < 18; ++i)
        {
            if ((i / 3 == ROT_UP || i / 3 == ROT_DOWN)
                    || (i % 3 == 1))
            {
                newCoord1 = MoveTable::CornerPermutation[Q.top().coord1][i];
                newCoord2 = MoveTable::P2EdgePermutation[Q.top().coord2][i];
                unsigned int rep = Sym::RepTable::cornerPermutation[newCoord1].first;

                for (auto sym : Sym::RepTable::cornerPermutation[newCoord1].second)
                {
                    unsigned int newEdgeSym = Sym::MoveTable::P2EdgePermutation[newCoord2][sym]; 
                    newIndex = newEdgeSym * 2768 + rep;
                    if (PruneTable::Get::value_P2_CPEP(newIndex) == 0)
                    {
                        PruneTable::Set::value_P2_CPEP(newIndex, ((Q.top().depht + 1) % 3) + 1);
                        Q.emplace(Sym::Rep::cornerPermutation[rep], newEdgeSym, Q.top().depht + 1);
                    }
                }
            }
        }
        Q.pop();
    }
}

int     Kociemba::PruneTable::Generate::all()
{
    std::filesystem::create_directories("./data");

    if (std::filesystem::exists("./data/P1"))
    {
        std::ifstream fileP1;
        fileP1.open("./data/P1");
        if (fileP1.is_open())
        {
            fileP1.seekg(0, std::ios::end);
            size_t l = fileP1.tellg();
            fileP1.seekg(0, std::ios::beg);
            if (l > 35227103)
                l = 35227103;
            fileP1.read(Kociemba::PruneTable::P1, l);
            fileP1.close();
        }
        else
        {
            std::cerr << "Error: Cannot Read File '" << "./data/P1" << "'." << std::endl;
            return (1);
        }
    }
    else
    {
        std::ofstream fileP1;
        fileP1.open("./data/P1");
        if (fileP1.is_open())
        {
            std::cout << "Generating " << "Phase 1" << " PruneTable ..." << std::endl;
            Kociemba::PruneTable::Generate::P1();
            if(!fileP1.write(Kociemba::PruneTable::P1, 35227103))
            {
                fileP1.close();
                std::cerr << "Error: Failed to Write in File '" << "./data/P1" << "'." << std::endl;
                return (1);
            }
            fileP1.close();
        }
        else
        {
            std::cerr << "Error: Cannot Write File '" << "./data/P1" << "'." << std::endl;
            return (1);
        }
    }


    if (std::filesystem::exists("./data/P2_CPEP"))
    {
        std::ifstream fileP2_CPEP;
        fileP2_CPEP.open("./data/P2_CPEP");
        if (fileP2_CPEP.is_open())
        {
            fileP2_CPEP.seekg(0, std::ios::end);
            size_t l = fileP2_CPEP.tellg();
            fileP2_CPEP.seekg(0, std::ios::beg);
            if (l > 27901440)
                l = 27901440;
            fileP2_CPEP.read(Kociemba::PruneTable::P2_CPEP, l);
            fileP2_CPEP.close();
        }
        else
        {
            std::cerr << "Error: Cannot Read File '" << "./data/P2_CPEP" << "'." << std::endl;
            return (1);
        }
    }
    else
    {
        std::ofstream fileP2_CPEP;
        fileP2_CPEP.open("./data/P2_CPEP");
        if (fileP2_CPEP.is_open())
        {
            std::cout << "Generating " << "Phase 2 CPEP" << " PruneTable ..." << std::endl;
            Kociemba::PruneTable::Generate::P2_CPEP();
            if(!fileP2_CPEP.write(Kociemba::PruneTable::P2_CPEP, 27901440))
            {
                fileP2_CPEP.close();
                std::cerr << "Error: Failed to Write in File '" << "./data/P2_CPEP" << "'." << std::endl;
                return (1);
            }
            fileP2_CPEP.close();
        }
        else
        {
            std::cerr << "Error: Cannot Write File '" << "./data/P2_CPEP" << "'." << std::endl;
            return (1);
        }
    }

    return (0);
}