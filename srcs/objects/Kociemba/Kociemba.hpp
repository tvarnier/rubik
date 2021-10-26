#ifndef KOCIEMBA_HPP
# define KOCIEMBA_HPP

# include <set>
# include <unordered_set>
# include <fstream>
# include <queue>

# include "../Cube/Cube.hpp"
class Cube;

# define CORNER_ORIENTATION_MOVETABLE_SIZE  2187
# define EDGE_ORIENTATION_MOVETABLE_SIZE    2048
# define UD_SLICE_MOVETABLE_SIZE            495
# define FLIP_UD_SLICE_MOVETABLE_SIZE       1013760

# define UD_SLICE_SORTED_MOVETABLE_SIZE     11880

# define CORNER_PERMUTATION_MOVETABLE_SIZE  40320
# define P2_EDGE_PERMUTATION_MOVETABLE_SIZE 40320
# define P2_UD_SLICE_MOVETABLE_SIZE         24

# define P1_NBR_MOVE 18
# define P2_NBR_MOVE 10

class   Kociemba
{
    public:
        static int      init();
        static std::vector<std::string>    solve(Cube& rubik);


    private:
        static char     P1_PruneTable[35227103];
        static char     P2_CPEP_PruneTable[27901440];

        static std::vector< std::array<unsigned int, 18> >  CornerOrientation_MoveTable;
        static std::vector< std::array<unsigned int, 18> >  EdgeOrientation_MoveTable  ;
        static std::vector< std::array<unsigned int, 18> >  UDSlice_MoveTable          ;
        static std::vector< std::array<unsigned int, 18> >  FlipUDSlice_MoveTable      ;

        static std::vector< std::array<unsigned int, 18> >  UDSliceSorted_MoveTable    ;
        static std::vector< std::array<unsigned int, 18> >  FBSliceSorted_MoveTable    ;
        static std::vector< std::array<unsigned int, 18> >  RLSliceSorted_MoveTable    ;

        static std::vector< std::array<unsigned int, 18> >  CornerPermutation_MoveTable;
        static std::vector< std::array<unsigned int, 18> >  P2EdgePermutation_MoveTable;
        static std::vector< std::array<unsigned int, 18> >  P2UDSlice_MoveTable        ;

        static std::vector< std::array<unsigned int, 24> > edge8Perm;

        static std::vector< unsigned int >    CornPerm_SymRep;
        static std::vector< std::pair< unsigned int, std::vector<unsigned int> > >  CornPerm_Sym;

        static std::vector< unsigned int >    FlipUDSlice_SymRep;
        static std::vector< std::pair< unsigned int, std::vector<unsigned int> > >  FlipUDSlice_Sym;

        static std::vector< std::array<unsigned int, 16> > P2EdgePermSym_MoveTable;
        static std::vector< std::array<unsigned int, 16> > CornOrientSym_MoveTable;

        static std::vector< unsigned int >  CornerPermutation_DephtTable;

        static std::array< Cube, 48 >    symCubes;
        static std::array< Cube, 48 > symInvCubes;

        static void                     initContainers();

        //  Coordinates

        static unsigned int             cornerOrientationCoordinates(const std::array<unsigned int, 8>& cornerOrientation);
        static std::array<unsigned int, 8>     generateCornerOrientation(unsigned int coord);
        
        static unsigned int             cornerPermutationCoordinates(const std::array<CORNERS, 8>& cornerPermutation);
        static  std::array<CORNERS, 8>          generateCornerPermutation(unsigned int coord);

        static unsigned int                    edgeOrientationCoordinates(const std::array<unsigned int, 12>& edgeOrientation);
        static  std::array<unsigned int, 12>    generateEdgeOrientation(unsigned int coord);

        static unsigned int                    edgePermutationCoordinates(const std::array<EDGES, 12>& edgePermutation);

        static unsigned int                    phase2EdgePermutationCoordinates(const std::array<EDGES, 12>& edgePermutation);
        static std::array<EDGES, 12>           generateP2EdgePermutation(unsigned int coord);

        static unsigned int                    UDSliceCoordinates(const std::array<EDGES, 12>& edgePermutation);
        static std::array<EDGES, 12>           generateUDSlice(unsigned int coord);

        static unsigned int                    P2UDSliceCoordinates(const std::array<EDGES, 12>& edgePermutation);
        static std::array<EDGES, 12>           generateP2UDSlice(unsigned int coord);

        static unsigned int                    UDSliceSortedCoordinates(const std::array<EDGES, 12>& edgePermutation);
        static std::array<EDGES, 12>           generateUDSliceSorted(unsigned int coord);

        static unsigned int                    FBSliceSortedCoordinates(const std::array<EDGES, 12>& edgePermutation);
        static std::array<EDGES, 12>           generateFBSliceSorted(unsigned int coord);

        static unsigned int                    RLSliceSortedCoordinates(const std::array<EDGES, 12>& edgePermutation);
        static std::array<EDGES, 12>           generateRLSliceSorted(unsigned int coord);
    
        // Symmetries

        static void    generate_symmetries();
        static void    generate_symCubes();
        static void    generate_symInvCubes();

        static unsigned int    getCornPermSymRep(const std::array<CORNERS, 8> cornPerm);

        //  MoveTables

        static int     generate_moveTables();

        static void    generate_CornerOrientation_MoveTable();
        static void    generate_CornerOrientationSym_Movetable();

        static void    generate_EdgeOrientation_MoveTable();
        static void    generate_UDSlice_MoveTable();

        static void    generateFlipUDSliceRep();
        static void    getFLipUDSliceRep();
        static void    generate_FlipUDSlice_MoveTable();
        static void    generate_FlipUDSliceSym_MoveTable();
        
        static void    generate_UDSliceSorted_MoveTable();
        static void    generate_RLSliceSorted_MoveTable();
        static void    generate_FBSliceSorted_MoveTable();

        static void    generate_CornerPermutation_MoveTable();
        static void    generate_CornerPermutationSym_MoveTable();
        
        static void    generate_P2EdgePermutation_MoveTable();
        static void    generate_P2EdgePermutationSym_MoveTable();

        static void    generate_P2UDSlice_MoveTable();

        static void    generateEdge8Perm();

        //  PruneTables

        static int     generate_pruneTables();
        
        static void    generatePruneTable_P1();
        static void    generatePruneTable_P2();

        static char    getValue_P1_PruneTable(unsigned long long index);
        static void    setValue_P1_PruneTable(unsigned long long index, char value);

        static char    getValue_P2_CPEP_PruneTable(unsigned long long index);
        static void    setValue_P2_CPEP_PruneTable(unsigned long long index, char value);


        // Depht Tables

        static void            generate_dephtTables();

        static void            generate_DephtTable(
            unsigned int (*getValue_moveTable)(unsigned int index, unsigned int move),
            void         (*setValue_dephtTable)(unsigned int index, unsigned int depht),
            unsigned int (*getValue_dephtTable)(unsigned int index)
        );

        static unsigned int    getValue_CornPerm_MoveTable(unsigned int index, unsigned int move);
        static void            setValue_CornPerm_DephtTable(unsigned int index, unsigned int depht);
        static unsigned int    getValue_CornPerm_DephtTable(unsigned int index);

        // Solve

        struct P1 {
            unsigned int        cornOrient;
            unsigned int        flipUDSlice;
            unsigned int        UDSliceSorted;
            unsigned int        RLSliceSorted;
            unsigned int        FBSliceSorted;
            uint8_t             pruning;
            size_t              depht;
            unsigned int        nbrMove;

            P1(unsigned int co = 0, unsigned int fus = 0, unsigned int uss = 0, unsigned int rls = 0, unsigned int fbs = 0, uint8_t p = 0, size_t d = 0) :
            cornOrient(co), flipUDSlice(fus), UDSliceSorted(uss), RLSliceSorted(rls), FBSliceSorted(fbs), pruning(p), depht(d) {}
        };

        struct P2 {
            unsigned int        cornPerm;
            unsigned int        edgePerm;
            unsigned int        UDSlice;
            uint8_t             CPEP;
            size_t              depht;
            unsigned int        cornPermDepht;

            P2(unsigned int cp = 0, unsigned int ep = 0, unsigned int us = 0, uint8_t cpep = 0, size_t d= 0, unsigned int cpDepht = 0) :
            cornPerm(cp), edgePerm(ep), UDSlice(us), CPEP(cpep), depht(d), cornPermDepht(cpDepht) {}
        };

        struct SolvingState {
            struct P1           p1;
            struct P2           p2;
            short               phase;
            int                 depht;
            std::vector<int>    path;
            size_t              pathHash;
            int                 lastMove;

            SolvingState( struct P1 phase1 = P1(), struct P2 phase2 = P2(),
                          short ph = 1, int d = 0, const std::vector<int>& p = std::vector<int>(), size_t pHash = 0, int lm = -1)
            : p1(phase1), p2(phase2), phase(ph), depht(d), path(p), pathHash(pHash), lastMove(lm) {}

            bool operator<(const SolvingState& other) const { return ((depht == other.depht) ? ((path.size() == other.path.size()) ? pathHash < other.pathHash : path.size() < other.path.size()) : depht < other.depht); }
            bool operator==(const SolvingState& other) const { return (pathHash == other.pathHash); }
        };

        static void    solveP1(Cube& rubik);
        static void    solveP2(SolvingState current, const Cube& rubik);

        static size_t  getP1Length(unsigned int cornOrient, unsigned int flipUdSlice, uint8_t pruning);
        static size_t  getP2Length(unsigned int cornPerm, unsigned int edgePerm, uint8_t pruning);

        static bool    isStateUseless(const short& phase, const unsigned int& size, const P1& phase1, const P2& phase2);

        static void    generateChilds(std::set<SolvingState>& open, std::unordered_set<size_t>& close, SolvingState& current, const Cube& rubik);
        static void    solveSucess(const Cube& rubik, SolvingState& solution);
};

#endif