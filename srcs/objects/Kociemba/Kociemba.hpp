#ifndef KOCIEMBA_HPP
# define KOCIEMBA_HPP

# include "../Cube/Cube.hpp"
class Cube;

# include "rubik.hpp"

# define P2_EDGE_PERMUTATION_MOVETABLE_SIZE 40320
# define CORNER_PERMUTATION_MOVETABLE_SIZE  40320

# define P1_NBR_MOVE 16
# define P2_NBR_MOVE 10

class   Kociemba
{
    public: 
        int             generate_moveTables();
        int             generate_Dephts();
        int             solve(Cube rubik);

        const static std::map<std::string, Cube::moveFunction>  P1MoveMap;
        const static std::map<std::string, Cube::moveFunction>  P2MoveMap;
        
        std::vector< std::pair<std::vector<unsigned int>, unsigned int> >   CornerPermutation_MoveTable {};
        std::vector< std::pair<std::vector<unsigned int>, unsigned int> >   P2EdgePermutation_MoveTable {};

        //  Coordinates

        static unsigned int             cornerOrientationCoordinates(const std::array<unsigned int, 8>& cornerOrientation);
        static unsigned int             cornerPermutationCoordinates(const std::array<CORNERS, 8>& cornerPermutation);

        std::array<CORNERS, 8>          generateCornerPermutation(unsigned int coord);
        std::array<EDGES, 12>           generateP2EdgePermutation(unsigned int coord);

        unsigned int                    edgeOrientationCoordinates(const std::array<unsigned int, 12>& edgeOrientation);
        unsigned int                    edgePermutationCoordinates(const std::array<EDGES, 12>& edgePermutation);

        unsigned int                    phase2EdgePermutationCoordinates(const std::array<EDGES, 12>& edgePermutation);

        unsigned int                    UDSliceCoordinates(const std::array<EDGES, 12>& edgePermutation);
        unsigned int                    UDSliceSortedCoordinates(const std::array<EDGES, 12>& edgePermutation);
        //  MoveTables

        void    generate_P2EdgePermutation_MoveTable();
        void    generate_CornerPermutation_MoveTable();

        //  Pattern DB

        void    generate_moveTableDepth(std::vector< std::pair<std::vector<unsigned int>, unsigned int> >& moveTable, int nbrMove);

        // Solve

        int     solveP2(Cube rubik);
};

#endif