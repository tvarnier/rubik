#ifndef KOCIEMBA_HPP
# define KOCIEMBA_HPP

# include "../Cube/Cube.hpp"
class Cube;

# include "rubik.hpp"

# define CORNER_ORIENTATION_MOVETABLE_SIZE  2187
# define EDGE_ORIENTATION_MOVETABLE_SIZE    2048
# define UD_SLICE_MOVETABLE_SIZE            495

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
        static char     P1_COEO_PruneTable[1119744];
        static char     P1_COUS_PruneTable[270642];
        static char     P1_USEO_PruneTable[253440];
        static char     P2_CPEP_PruneTable[406425600];
        static char     P2_CPUS_PruneTable[241920];
        static char     P2_USEP_PruneTable[241920];

        std::array< std::array<unsigned int, 18>,  CORNER_ORIENTATION_MOVETABLE_SIZE >  CornerOrientation_MoveTable {};
        std::array< std::array<unsigned int, 18>,    EDGE_ORIENTATION_MOVETABLE_SIZE >  EdgeOrientation_MoveTable   {};
        std::array< std::array<unsigned int, 18>,            UD_SLICE_MOVETABLE_SIZE >  UdSlice_MoveTable           {};

        std::array< std::array<unsigned int, 18>, P2_EDGE_PERMUTATION_MOVETABLE_SIZE >  CornerPermutation_MoveTable {};
        std::array< std::array<unsigned int, 18>,  CORNER_PERMUTATION_MOVETABLE_SIZE >  P2EdgePermutation_MoveTable {};
        std::array< std::array<unsigned int, 18>,     UD_SLICE_SORTED_MOVETABLE_SIZE >  UdSliceSorted_MoveTable     {};

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
    
        //  MoveTables

        int     generate_moveTables();

        void    generate_CornerOrientation_MoveTable();
        void    generate_EdgeOrientation_MoveTable();
        void    generate_UdSlice_MoveTable();

        void    generate_CornerPermutation_MoveTable();
        void    generate_P2EdgePermutation_MoveTable();
        void    generate_UdSliceSorted_MoveTable();

        //  PruneTables

        void    generate_pruneTables();

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

        //  Solve

        void    solveP1(Cube& rubik);
        void    solveP2(Cube& rubik);
};

#endif