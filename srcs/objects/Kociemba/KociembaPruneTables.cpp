#include "Kociemba.hpp"

char    Kociemba::getValue_P1_PruneTable(unsigned long long index) { return ( (Kociemba::P1_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::setValue_P1_PruneTable(unsigned long long index, char value) { Kociemba::P1_PruneTable[index / 4] =  Kociemba::P1_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }

char    Kociemba::getValue_P2_PruneTable(unsigned long long index) { return ( (Kociemba::P2_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::setValue_P2_PruneTable(unsigned long long index, char value) { Kociemba::P2_PruneTable[index / 4] =  Kociemba::P2_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }

/* ============================ COEO ============================ */

char    Kociemba::getValue_P1_COEO_PruneTable(unsigned long long index) { return ( (Kociemba::P1_COEO_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::setValue_P1_COEO_PruneTable(unsigned long long index, char value) { Kociemba::P1_COEO_PruneTable[index / 4] =  Kociemba::P1_COEO_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }
void    Kociemba::getNewCoords_COEO(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2) {
    newCoord1 = CornerOrientation_MoveTable[coord1][moveId];
    newCoord2 = EdgeOrientation_MoveTable[coord2][moveId];
}
void    Kociemba::fileRead_COEO(std::ifstream& file, size_t length) { file.read(P1_COEO_PruneTable, length); }
int     Kociemba::filePut_COEO(std::string filename) {
    FILE *file = fopen(std::string("./pruningTables/" + filename).c_str(), "w");
    int results = fputs(P1_COEO_PruneTable, file);
    if (results == EOF) {
        std::printf("FAIL TO WRITE\n");
    }
    fclose(file);
    return (0);
}

/* ============================ COUS ============================ */

char    Kociemba::getValue_P1_COUS_PruneTable(unsigned long long index) { return ( (Kociemba::P1_COUS_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::setValue_P1_COUS_PruneTable(unsigned long long index, char value) { Kociemba::P1_COUS_PruneTable[index / 4] =  Kociemba::P1_COUS_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }
void    Kociemba::getNewCoords_COUS(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2) {
    newCoord1 = CornerOrientation_MoveTable[coord1][moveId];
    newCoord2 = UdSlice_MoveTable[coord2][moveId];
}
void    Kociemba::fileRead_COUS(std::ifstream& file, size_t length) { file.read(P1_COUS_PruneTable, length); }
int     Kociemba::filePut_COUS(std::string filename) {
    FILE *file = fopen(std::string("./pruningTables/" + filename).c_str(), "w");
    int results = fputs(P1_COUS_PruneTable, file);
    if (results == EOF) {
        std::printf("FAIL TO WRITE\n");
    }
    fclose(file);
    return (0);
}

/* ============================ USEO ============================ */

char    Kociemba::getValue_P1_USEO_PruneTable(unsigned long long index) { return ( (Kociemba::P1_USEO_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::setValue_P1_USEO_PruneTable(unsigned long long index, char value) { Kociemba::P1_USEO_PruneTable[index / 4] =  Kociemba::P1_USEO_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }
void    Kociemba::getNewCoords_USEO(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2) {
    newCoord1 = UdSlice_MoveTable[coord1][moveId];
    newCoord2 = EdgeOrientation_MoveTable[coord2][moveId];
}
void    Kociemba::fileRead_USEO(std::ifstream& file, size_t length) { file.read(P1_USEO_PruneTable, length); }
int     Kociemba::filePut_USEO(std::string filename) {
    FILE *file = fopen(std::string("./pruningTables/" + filename).c_str(), "w");
    int results = fputs(P1_USEO_PruneTable, file);
    if (results == EOF) {
        std::printf("FAIL TO WRITE\n");
    }
    fclose(file);
    return (0);
}

/* ============================ CPEP ============================ */

char    Kociemba::getValue_P2_CPEP_PruneTable(unsigned long long index) { return ( (Kociemba::P2_CPEP_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 ); }
void    Kociemba::setValue_P2_CPEP_PruneTable(unsigned long long index, char value) { Kociemba::P2_CPEP_PruneTable[index / 4] =  Kociemba::P2_CPEP_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) ); }
void    Kociemba::getNewCoords_CPEP(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2) {
    newCoord1 = CornerPermutation_MoveTable[coord1][moveId];
    newCoord2 = P2EdgePermutation_MoveTable[coord2][moveId];
}
void    Kociemba::fileRead_CPEP(std::ifstream& file, size_t length) { file.read(P2_CPEP_PruneTable, length); }
int     Kociemba::filePut_CPEP(std::string filename) {
    FILE *file = fopen(std::string("./pruningTables/" + filename).c_str(), "w");
    int results = fputs(P2_CPEP_PruneTable, file);
    if (results == EOF) {
        std::printf("FAIL TO WRITE\n");
    }
    fclose(file);
    return (0);
}

/* ============================ CPUS ============================ */

char    Kociemba::getValue_P2_CPUS_PruneTable(unsigned long long index)
{
    return ( (Kociemba::P2_CPUS_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 );
}

void    Kociemba::setValue_P2_CPUS_PruneTable(unsigned long long index, char value)
{
    Kociemba::P2_CPUS_PruneTable[index / 4] =  Kociemba::P2_CPUS_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) );
}

void    Kociemba::getNewCoords_CPUS(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2)
{
    newCoord1 = CornerPermutation_MoveTable[coord1][moveId];
    newCoord2 = UdSliceSorted_MoveTable[coord2][moveId];
}

void    Kociemba::fileRead_CPUS(std::ifstream& file, size_t length) { file.read(P2_CPUS_PruneTable, length); }
int     Kociemba::filePut_CPUS(std::string filename) {
    FILE *file = fopen(std::string("./pruningTables/" + filename).c_str(), "w");
    int results = fputs(P2_CPUS_PruneTable, file);
    if (results == EOF) {
        std::printf("FAIL TO WRITE\n");
    }
    fclose(file);
    return (0);
}

/* ============================ USEP ============================ */

char    Kociemba::getValue_P2_USEP_PruneTable(unsigned long long index)
{
    return ( (Kociemba::P2_USEP_PruneTable[index / 4] >> (6 - ((index % 4) * 2))) & 3 );
}

void    Kociemba::setValue_P2_USEP_PruneTable(unsigned long long index, char value)
{
    Kociemba::P2_USEP_PruneTable[index / 4] =  Kociemba::P2_USEP_PruneTable[index / 4] | ( value << (6 - ((index % 4) * 2)) );
}

void    Kociemba::getNewCoords_USEP(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2)
{
    newCoord1 = UdSliceSorted_MoveTable[coord1][moveId];
    newCoord2 = P2EdgePermutation_MoveTable[coord2][moveId];
}
void    Kociemba::fileRead_USEP(std::ifstream& file, size_t length) { file.read(P2_USEP_PruneTable, length); }
int     Kociemba::filePut_USEP(std::string filename) {
    FILE *file = fopen(std::string("./pruningTables/" + filename).c_str(), "w");
    int results = fputs(P2_USEP_PruneTable, file);
    if (results == EOF) {
        std::printf("FAIL TO WRITE\n");
    }
    fclose(file);
    return (0);
}

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

struct StateP1 {
    unsigned int    coord1;
    unsigned int    coord2;
    unsigned int    coord3;
    unsigned int    depht;

    StateP1(unsigned int c1 = 0, unsigned int c2 = 0, unsigned int c3 = 0, unsigned int d = 0)
    : coord1(c1), coord2(c2), coord3(c3), depht(d) {}

    bool operator<(const StateP1& other) const
    {
        return depht > other.depht;
    }
};

void    Kociemba::generatePruneTable_P1()
{
    std::priority_queue<StateP1>    Q;
    unsigned int                    newCoord1;
    unsigned int                    newCoord2;
    unsigned int                    newCoord3;

    unsigned long long              newIndex;

    unsigned long long              size(1);
    unsigned long long              lastSize(1);
    unsigned int                    lastDepht(0);

    Q.emplace(0, 0, 0, 0);
    setValue_P1_PruneTable(0, 1);

    while (!Q.empty())
    {
        for (unsigned int i = 0; i < P1_NBR_MOVE; ++i)
        {
            if (Q.top().depht != lastDepht)
            {
                std::printf("Depht : %u - %llu\n", Q.top().depht, size - lastSize);
                lastSize = size;
                lastDepht = Q.top().depht;
            }
            newCoord1 = CornerOrientation_MoveTable[Q.top().coord1][i];
            newCoord2 = EdgeOrientation_MoveTable[Q.top().coord2][i];
            newCoord3 = UdSlice_MoveTable[Q.top().coord3][i];
            newIndex = newCoord1 * EDGE_ORIENTATION_MOVETABLE_SIZE * UD_SLICE_MOVETABLE_SIZE + newCoord2 * UD_SLICE_MOVETABLE_SIZE+ newCoord3;
            if (getValue_P1_PruneTable(newIndex) == 0)
            {
                setValue_P1_PruneTable(newIndex, ((Q.top().depht + 1) % 3) + 1);
                Q.emplace(newCoord1, newCoord2, newCoord3, Q.top().depht + 1);
                ++size;
            }
        }
        Q.pop();
    }
    lib::printendl("Size :: ", size);
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
    setValue_P2_PruneTable(0, 1);

    while (!Q.empty())
    {
        for (unsigned int i = 0; i < 18; ++i)
        {
            if ((i / 3 == UP || i / 3 == DOWN)
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
                unsigned int rep = CornSym[newCoord1].first;

                bool created = false;

                for (auto sym : CornSym[newCoord1].second)
                {
                    unsigned int newEdgeSym = phase2EdgePermutationCoordinates(Cube::multEdgePerm( Cube::multEdgePerm(symInvCubes[sym].m_edges.p, generateP2EdgePermutation(newCoord2)), symCubes[sym].m_edges.p ));
                    
                    newIndex = newEdgeSym * 2768 + rep;
                    if (getValue_P2_PruneTable(newIndex) == 0)
                    {
                        setValue_P2_PruneTable(newIndex, ((Q.top().depht + 1) % 3) + 1);
                        Q.emplace(CornSymRep[rep], newEdgeSym, Q.top().depht + 1);
                        ++size;
                    }
                }
                if (created)
                {
                }
            }
        }
        Q.pop();
    }
    lib::printendl("Size :: ", size);
}

void    Kociemba::generatePruneTable(
    unsigned int c1size,
    unsigned int c2Size,
    int nbrMoves,
    void (Kociemba::*set)(unsigned long long, char),
    char (Kociemba::*get)(unsigned long long),
    void (Kociemba::*getNewCoords)(int, const unsigned int&, const unsigned int&, unsigned int&, unsigned int&)
)
{
    std::priority_queue<StatePruning>    Q;
    unsigned int                    newCoord1;
    unsigned int                    newCoord2;
    unsigned long long              newIndex;

    unsigned long long              size(1);

    unsigned long long              lastSize(1);

    unsigned int                    lastDepht(0);

    Q.emplace(0, 0, 0);
    (this->*set)(0, 1);

    while (!Q.empty())
    {
        for (unsigned int i = 0; i < nbrMoves; ++i)
        {
            if (Q.top().depht != lastDepht)
            {
                std::printf("Depht : %u - %llu\n", Q.top().depht, size - lastSize);
                lastSize = size;
                lastDepht = Q.top().depht;
            }
            (this->*getNewCoords)(i, Q.top().coord1, Q.top().coord2, newCoord1, newCoord2);
            newIndex = newCoord1 * c2Size + newCoord2;
            if ((this->*get)(newIndex) == 0)
            {
                (this->*set)(newIndex, ((Q.top().depht + 1) % 3) + 1);
                Q.emplace(newCoord1, newCoord2, Q.top().depht + 1);
                ++size;
            }
        }
        Q.pop();
    }
    lib::printendl("Size :: ", size);
}

/* ============================ ---- ============================ */

void    Kociemba::create_pruneTable(
    std::string filename,
    unsigned long long size,
    unsigned int c1size,
    unsigned int c2Size,
    int nbrMoves,
    void (Kociemba::*set)(unsigned long long, char),
    char (Kociemba::*get)(unsigned long long),
    void (Kociemba::*getNewCoords)(int, const unsigned int&, const unsigned int&, unsigned int&, unsigned int&),
    void (Kociemba::*fileRead)(std::ifstream&, size_t),
    int  (Kociemba::*filePut)(std::string)
)
{
    std::ifstream file;
    file.open(std::string("./pruningTables/" + filename).c_str());
    if (file)
    {
        lib::printendl("Loading " + filename + " Prune Table ...");
        file.seekg(0, std::ios::end);
        size_t length = file.tellg();
        file.seekg(0, std::ios::beg);
        if (length > size)
        {
            length = size;
        }
        (this->*fileRead)(file, length);
    }
    else
    {
        lib::printendl("Creating " + filename + " Prune Table ...");
        generatePruneTable(
            c1size,
            c2Size,
            nbrMoves, 
            set,
            get,
            getNewCoords
        );
        (this->*filePut)(filename);
        lib::printendl(filename + " Prune Table Created.");
    }
}

/* ============================ ---- ============================ */

void    Kociemba::generate_pruneTables()
{
    std::ifstream fileP1;
    fileP1.open(std::string("./pruningTables/P1").c_str());
    if (fileP1)
    {
        lib::printendl("Loading P1 Prune Table ...");
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
        lib::printendl("Creating P1 Prune Table ...");
        generatePruneTable_P1();

        FILE *file = fopen(std::string("./pruningTables/P1").c_str(), "w");
        int results = fputs(P1_PruneTable, file);
        if (results == EOF) {
            std::printf("FAIL TO WRITE\n");
        }
        fclose(file);

        lib::printendl("P1 Prune Table Created.");
    }



    std::ifstream fileP2;
    fileP2.open(std::string("./pruningTables/P2").c_str());
    if (fileP2)
    {
        lib::printendl("Loading P2 Prune Table ...");
        fileP2.seekg(0, std::ios::end);
        size_t length = fileP2.tellg();
        fileP2.seekg(0, std::ios::beg);
        if (length > 27901440)
        {
            length = 27901440;
        }
        fileP2.read(P2_PruneTable, length);
    }
    else
    {
        lib::printendl("Creating P2 Prune Table ...");
        generatePruneTable_P2();

        FILE *file = fopen(std::string("./pruningTables/P2").c_str(), "w");
        int results = fputs(P2_PruneTable, file);
        if (results == EOF) {
            std::printf("FAIL TO WRITE\n");
        }
        fclose(file);

        lib::printendl("P2 Prune Table Created.");
    }

    //////////////////////////////////////////////////////////////

    create_pruneTable(
        "P1_COEO",
        1119744,
        CORNER_ORIENTATION_MOVETABLE_SIZE,
        EDGE_ORIENTATION_MOVETABLE_SIZE,
        P1_NBR_MOVE, 
        &Kociemba::setValue_P1_COEO_PruneTable,
        &Kociemba::getValue_P1_COEO_PruneTable,
        &Kociemba::getNewCoords_COEO,
        &Kociemba::fileRead_COEO,
        &Kociemba::filePut_COEO
    );
    ///////////////////////////////////////////////////////////////////////
    create_pruneTable(
        "P1_COUS",
        270642,
        CORNER_ORIENTATION_MOVETABLE_SIZE,
        UD_SLICE_MOVETABLE_SIZE,
        P1_NBR_MOVE, 
        &Kociemba::setValue_P1_COUS_PruneTable,
        &Kociemba::getValue_P1_COUS_PruneTable,
        &Kociemba::getNewCoords_COUS,
        &Kociemba::fileRead_COUS,
        &Kociemba::filePut_COUS
    );
    ///////////////////////////////////////////////////////////////////////
    create_pruneTable(
        "P1_USEO",
        253440,
        UD_SLICE_MOVETABLE_SIZE,
        EDGE_ORIENTATION_MOVETABLE_SIZE,
        P1_NBR_MOVE, 
        &Kociemba::setValue_P1_USEO_PruneTable,
        &Kociemba::getValue_P1_USEO_PruneTable,
        &Kociemba::getNewCoords_USEO,
        &Kociemba::fileRead_USEO,
        &Kociemba::filePut_USEO
    );

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    
    create_pruneTable(
        "P2_CPEP",
        406425600,
        CORNER_PERMUTATION_MOVETABLE_SIZE,
        P2_EDGE_PERMUTATION_MOVETABLE_SIZE,
        P2_NBR_MOVE, 
        &Kociemba::setValue_P2_CPEP_PruneTable,
        &Kociemba::getValue_P2_CPEP_PruneTable,
        &Kociemba::getNewCoords_CPEP,
        &Kociemba::fileRead_CPEP,
        &Kociemba::filePut_CPEP
    );
    ///////////////////////////////////////////////////////////////////////
    create_pruneTable(
        "P2_CPUS",
        241920,
        CORNER_PERMUTATION_MOVETABLE_SIZE,
        UD_SLICE_SORTED_MOVETABLE_SIZE,
        P2_NBR_MOVE, 
        &Kociemba::setValue_P2_CPUS_PruneTable,
        &Kociemba::getValue_P2_CPUS_PruneTable,
        &Kociemba::getNewCoords_CPUS,
        &Kociemba::fileRead_CPUS,
        &Kociemba::filePut_CPUS
    );
    ///////////////////////////////////////////////////////////////////////
    create_pruneTable(
        "P2_USEP",
        241920,
        UD_SLICE_SORTED_MOVETABLE_SIZE,
        P2_EDGE_PERMUTATION_MOVETABLE_SIZE,
        P2_NBR_MOVE, 
        &Kociemba::setValue_P2_USEP_PruneTable,
        &Kociemba::getValue_P2_USEP_PruneTable,
        &Kociemba::getNewCoords_USEP,
        &Kociemba::fileRead_USEP,
        &Kociemba::filePut_USEP
    );
}