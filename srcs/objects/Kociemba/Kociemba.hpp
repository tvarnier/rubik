#ifndef KOCIEMBA_HPP
# define KOCIEMBA_HPP

# include "../Cube/Cube.hpp"
class Cube;

# include "rubik.hpp"

# define CORNER_ORIENTATION_MOVETABLE_SIZE  2187
# define EDGE_ORIENTATION_MOVETABLE_SIZE    2048
# define UD_SLICE_MOVETABLE_SIZE            495
# define FLIP_UD_SLICE_MOVETABLE_SIZE       1013760

# define CORNER_PERMUTATION_MOVETABLE_SIZE  40320
# define P2_EDGE_PERMUTATION_MOVETABLE_SIZE 40320
# define UD_SLICE_SORTED_MOVETABLE_SIZE     24

# define P1_NBR_MOVE 18
# define P2_NBR_MOVE 10

class   Kociemba
{
    public:
        Kociemba();
        void    solve(Cube rubik);

    private:
        static char     P1_PruneTable[35227103];
        //static char     P2_PruneTable[27901440];
        static char     P2_CPEP_PruneTable[27901440];
        static char     P2_CPUS_PruneTable[241920];
        static char     P2_USEP_PruneTable[241920];

        std::array< std::array<unsigned int, 18>,  CORNER_ORIENTATION_MOVETABLE_SIZE >  CornerOrientation_MoveTable {};
        std::array< std::array<unsigned int, 18>,    EDGE_ORIENTATION_MOVETABLE_SIZE >  EdgeOrientation_MoveTable   {};
        std::array< std::array<unsigned int, 18>,            UD_SLICE_MOVETABLE_SIZE >  UdSlice_MoveTable           {};
        std::vector< std::array<unsigned int, 18> >  FlipUdSlice_MoveTable       {};

        std::array< std::array<unsigned int, 18>,  CORNER_PERMUTATION_MOVETABLE_SIZE >  CornerPermutation_MoveTable {};
        std::array< std::array<unsigned int, 18>, P2_EDGE_PERMUTATION_MOVETABLE_SIZE >  P2EdgePermutation_MoveTable {};
        std::array< std::array<unsigned int, 18>,     UD_SLICE_SORTED_MOVETABLE_SIZE >  UdSliceSorted_MoveTable     {};

        std::array< unsigned int,  CORNER_PERMUTATION_MOVETABLE_SIZE >                  CornerPermutation_DephtTable {};
        std::array< unsigned int, P2_EDGE_PERMUTATION_MOVETABLE_SIZE >                  EdgePermutation_DephtTable {};
        std::array< unsigned int,     UD_SLICE_SORTED_MOVETABLE_SIZE >                  UdSliceSorted_DephtTable {};

        std::array< Cube, 16 >    symCubes {};
        std::array< Cube, 16 > symInvCubes {};

        std::array< unsigned int, 2768 >    CornPerm_SymRep {};
        std::array< std::pair< unsigned int, std::vector<unsigned int> >, CORNER_PERMUTATION_MOVETABLE_SIZE >    CornPerm_Sym {};

        std::array< unsigned int, 64430 >    FlipUdSlice_SymRep {};
        std::vector< std::pair< unsigned int, std::vector<unsigned int> > >    FlipUdSlice_Sym {};


        static std::vector< std::array<unsigned int, 16> > P2EdgePermSym_MoveTable;
        static std::vector< std::array<unsigned int, 16> > CornOrientSym_MoveTable;

        //  Coordinates

        static unsigned int             cornerOrientationCoordinates(const std::array<unsigned int, 8>& cornerOrientation);
        std::array<unsigned int, 8>     generateCornerOrientation(unsigned int coord);
        
        static unsigned int             cornerPermutationCoordinates(const std::array<CORNERS, 8>& cornerPermutation);
        std::array<CORNERS, 8>          generateCornerPermutation(unsigned int coord);

        unsigned int                    edgeOrientationCoordinates(const std::array<unsigned int, 12>& edgeOrientation);
        std::array<unsigned int, 12>    generateEdgeOrientation(unsigned int coord);

        unsigned int                    edgePermutationCoordinates(const std::array<EDGES, 12>& edgePermutation);

        unsigned int                    phase2EdgePermutationCoordinates(const std::array<EDGES, 12>& edgePermutation);
        std::array<EDGES, 12>           generateP2EdgePermutation(unsigned int coord);

        unsigned int                    UDSliceCoordinates(const std::array<EDGES, 12>& edgePermutation);
        std::array<EDGES, 12>           generateUDSlice(unsigned int coord);

        unsigned int                    UDSliceSortedCoordinates(const std::array<EDGES, 12>& edgePermutation);
        std::array<EDGES, 12>           generateUDSliceSorted(unsigned int coord);
    
        // Symmetries

        void    generate_symmetries();
        void    generate_symCubes();
        void    generate_symInvCubes();

        unsigned int    getCornPermSymRep(const std::array<CORNERS, 8> cornPerm);

        //  MoveTables

        int     generate_moveTables();

        void    generate_CornerOrientation_MoveTable();
        void    generate_EdgeOrientation_MoveTable();
        void    generate_UdSlice_MoveTable();

        void    generateFlipUdSLiceRep();
        void    getFLipUdSLiceRep();
        void    generate_FlipUdSlice_MoveTable();

        void    generate_CornerPermutation_MoveTable();
        void    generate_P2EdgePermutation_MoveTable();
        void    generate_UdSliceSorted_MoveTable();

        //  PruneTables

        void    generate_pruneTables();
        
        void    generatePruneTable_P1();
        void    generatePruneTable_P2();

        void    generatePruneTable(
            unsigned int c1size,
            unsigned int c2Size,
            int nbrMoves,
            void (Kociemba::*set)(unsigned long long, char),
            char (Kociemba::*get)(unsigned long long),
            void (Kociemba::*getNewCoords)(int, const unsigned int&, const unsigned int&, unsigned int&, unsigned int&)
        );
        void    create_pruneTable(
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
        );

        char    getValue_P1_PruneTable(unsigned long long index);
        void    setValue_P1_PruneTable(unsigned long long index, char value);

        // char    getValue_P2_PruneTable(unsigned long long index);
        // void    setValue_P2_PruneTable(unsigned long long index, char value);

        char    getValue_P1_COEO_PruneTable(unsigned long long index);
        void    setValue_P1_COEO_PruneTable(unsigned long long index, char value);
        void    getNewCoords_COEO(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2);
        void    fileRead_COEO(std::ifstream& file, size_t length);
        int     filePut_COEO(std::string filename);

        char    getValue_P1_COUS_PruneTable(unsigned long long index);
        void    setValue_P1_COUS_PruneTable(unsigned long long index, char value);
        void    getNewCoords_COUS(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2);
        void    fileRead_COUS(std::ifstream& file, size_t length);
        int     filePut_COUS(std::string filename);

        char    getValue_P1_USEO_PruneTable(unsigned long long index);
        void    setValue_P1_USEO_PruneTable(unsigned long long index, char value);
        void    getNewCoords_USEO(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2);
        void    fileRead_USEO(std::ifstream& file, size_t length);
        int     filePut_USEO(std::string filename);

        char    getValue_P2_CPEP_PruneTable(unsigned long long index);
        void    setValue_P2_CPEP_PruneTable(unsigned long long index, char value);
        void    getNewCoords_CPEP(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2);
        void    fileRead_CPEP(std::ifstream& file, size_t length);
        int     filePut_CPEP(std::string filename);

        char    getValue_P2_CPUS_PruneTable(unsigned long long index);
        void    setValue_P2_CPUS_PruneTable(unsigned long long index, char value);
        void    getNewCoords_CPUS(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2);
        void    fileRead_CPUS(std::ifstream& file, size_t length);
        int     filePut_CPUS(std::string filename);

        char    getValue_P2_USEP_PruneTable(unsigned long long index);
        void    setValue_P2_USEP_PruneTable(unsigned long long index, char value);
        void    getNewCoords_USEP(int moveId, const unsigned int& coord1, const unsigned int& coord2, unsigned int& newCoord1, unsigned int& newCoord2);
        void    fileRead_USEP(std::ifstream& file, size_t length);
        int     filePut_USEP(std::string filename);

        // Depht Tables

        void            generate_dephtTables();

        void            generate_DephtTable(
            unsigned int (Kociemba::*getValue_moveTable)(unsigned int index, unsigned int move),
            void         (Kociemba::*setValue_dephtTable)(unsigned int index, unsigned int depht),
            unsigned int (Kociemba::*getValue_dephtTable)(unsigned int index)
        );

        unsigned int    getValue_CornPerm_MoveTable(unsigned int index, unsigned int move);
        void            setValue_CornPerm_DephtTable(unsigned int index, unsigned int depht);
        unsigned int    getValue_CornPerm_DephtTable(unsigned int index);

        unsigned int    getValue_EdgePerm_MoveTable(unsigned int index, unsigned int move);
        void            setValue_EdgePerm_DephtTable(unsigned int index, unsigned int depht);
        unsigned int    getValue_EdgePerm_DephtTable(unsigned int index);

        unsigned int    getValue_UdSliceSorted_MoveTable(unsigned int index, unsigned int move);
        void            setValue_UdSliceSorted_DephtTable(unsigned int index, unsigned int depht);
        unsigned int    getValue_UdSliceSorted_DephtTable(unsigned int index);


        // Solve
        struct P1 {
            unsigned int        cornOrient;
            unsigned int        flipUdSlice;
            uint8_t             depht;
            bool                passedSol;

            P1(unsigned int co = 0, unsigned int fus = 0, uint8_t p1d = 0, unsigned int ps = false) :
            cornOrient(co), flipUdSlice(fus), depht(p1d), passedSol(ps) {}
        };

        struct P2 {
            unsigned int        cornPerm;
            unsigned int        edgePerm;
            unsigned int        udSliceSorted;
            uint8_t             CPEP;
            unsigned int        udSliceSortedDepht;


            P2(unsigned int cp = 0, unsigned int ep = 0, unsigned int uss = 0, uint8_t cpep = 0, unsigned int ussDepht = 0) :
            cornPerm(cp), edgePerm(ep), udSliceSorted(uss), CPEP(cpep), udSliceSortedDepht(ussDepht) {}
        };

        struct SolvingState {
            struct P1           p1;
            struct P2           p2;
            short               phase;
            int                 depht;
            std::vector<int>    path;
            int                 lastMove;

            SolvingState( struct P1 phase1 = P1(), struct P2 phase2 = P2(),
                          short ph = 1, int d = 0, const std::vector<int>& p = std::vector<int>(), int lm = -1)
            : p1(phase1), p2(phase2), phase(ph), depht(d), path(p), lastMove(lm) {}

            bool operator<(const SolvingState& other) const { return ((depht == other.depht) ? path.size() > other.path.size() : depht > other.depht); }
            bool operator==(const SolvingState& other) const { return (path == other.path); }
        };

        void    solveP1(Cube& rubik);
        void    solveP2(Cube& rubik);

        void    generateChilds(std::priority_queue<SolvingState>& open, std::unordered_set<size_t>& close, SolvingState& current, const Cube& rubik);
        void    solveSucess(Cube& rubik, SolvingState& solution, size_t& nbrOpenedStates);
};

#endif