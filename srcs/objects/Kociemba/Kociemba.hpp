#ifndef KOCIEMBA_HPP
# define KOCIEMBA_HPP

# include <set>
# include <unordered_set>
# include <fstream>
# include <queue>
# include <filesystem>
# include <iostream>
# include <algorithm>

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
        static int                          init();
        static std::vector<std::string>     solve(Cube& rubik);

    private:
        struct PruneTable {
            static char     P1[35227103];
            static char     P2_CPEP[27901440];

            struct Get {
                static char     value_P1(unsigned long long index);
                static char     value_P2_CPEP(unsigned long long index);
            };

            struct Set {
                static void     value_P1(unsigned long long index, char value);
                static void     value_P2_CPEP(unsigned long long index, char value);
            };

            struct Generate {
                static int      all();
                
                static void     P1();
                static void     P2_CPEP();

            };
        };

        struct MoveTable {
            static std::vector< std::array<unsigned int, 18> >  CornerOrientation;
            static std::vector< std::array<unsigned int, 18> >    EdgeOrientation;
            static std::vector< std::array<unsigned int, 18> >            UDSlice;
            static std::vector< std::array<unsigned int, 18> >        FlipUDSlice;
            static std::vector< std::array<unsigned int, 18> >      UDSliceSorted;
            static std::vector< std::array<unsigned int, 18> >      FBSliceSorted;
            static std::vector< std::array<unsigned int, 18> >      RLSliceSorted;
            static std::vector< std::array<unsigned int, 18> >  CornerPermutation;
            static std::vector< std::array<unsigned int, 18> >  P2EdgePermutation;
            static std::vector< std::array<unsigned int, 18> >          P2UDSlice;
            static std::vector< std::array<unsigned int, 24> >          edge8Perm;

            struct Generate {
                static int      all();

                static void     CornerOrientation();
                static void     EdgeOrientation();
                static void     UDSlice();
                static void     FlipUDSlice();
            
                static void     UDSliceSorted();
                static void     RLSliceSorted();
                static void     FBSliceSorted();

                static void     CornerPermutation();
                static void     P2EdgePermutation();
                static void     P2UDSlice();

                static void     Edge8Perm();
            };
        };

        //  Coordinates

        struct Coord {
            static unsigned int     cornerOrientation(const std::array<unsigned int, 8>&  cornerOrientation);
            static unsigned int     cornerPermutation(const std::array<CORNERS, 8>&       cornerPermutation);
            static unsigned int       edgeOrientation(const std::array<unsigned int, 12>& edgeOrientation);
            static unsigned int       edgePermutation(const std::array<EDGES, 12>&        edgePermutation);
            static unsigned int     P2EdgePermutation(const std::array<EDGES, 12>&        edgePermutation);
            static unsigned int               UDSlice(const std::array<EDGES, 12>&        edgePermutation);
            static unsigned int             P2UDSlice(const std::array<EDGES, 12>&        edgePermutation);
            static unsigned int         UDSliceSorted(const std::array<EDGES, 12>&        edgePermutation);
            static unsigned int         FBSliceSorted(const std::array<EDGES, 12>&        edgePermutation);
            static unsigned int         RLSliceSorted(const std::array<EDGES, 12>&        edgePermutation);

            struct Generate {
                static std::array<unsigned int, 8>      cornerOrientation(unsigned int coord);
                static std::array<CORNERS, 8>           cornerPermutation(unsigned int coord);
                static std::array<unsigned int, 12>       edgeOrientation(unsigned int coord);
                static std::array<EDGES, 12>            P2EdgePermutation(unsigned int coord);
                static std::array<EDGES, 12>                      UDSlice(unsigned int coord);
                static std::array<EDGES, 12>                    P2UDSlice(unsigned int coord);
                static std::array<EDGES, 12>                UDSliceSorted(unsigned int coord);
                static std::array<EDGES, 12>                FBSliceSorted(unsigned int coord);
                static std::array<EDGES, 12>                RLSliceSorted(unsigned int coord);      
            }; 
        };

        
        struct Sym {
            static std::array< Cube, 48 >    Cubes;
            static std::array< Cube, 48 > invCubes;

            struct MoveTable {
                static std::vector< std::array<unsigned int, 16> >  cornerOrientation;
                static std::vector< std::array<unsigned int, 16> >  P2EdgePermutation;
                struct Generate {
                    static void     cornerOrientation();
                    static void     P2EdgePermutation();
                };
            };

            struct Rep {
                static std::vector< unsigned int >  cornerPermutation;
                static std::vector< unsigned int >  FlipUDSlice;
                struct Generate {
                    static void     cornerPermutation();
                    static int      FlipUDSlice();
                };
            };
       
            struct RepTable {
                static std::vector< std::pair< unsigned int, std::vector<unsigned int> > >  cornerPermutation;
                static std::vector< std::pair< unsigned int, std::vector<unsigned int> > >  FlipUDSlice;
                struct Generate {
                    static void     generate_CornerPermutationSym_MoveTable();
                    static void     FlipUDSlice();
                };
            };

            struct Generate {
                static int      all();
                static void     Cubes();
                static void     invCubes();
            };
        };

        // Depht Tables

        struct DephtTable {
            static std::vector< unsigned int >  CornerPermutation;

            struct Generate {
                static void         all();
                static void         one(
                    std::vector< unsigned int >& dephtTable,
                    const std::vector< std::array<unsigned int, 18> >& moveTable,
                    int nbrMoves
                );
            };
        };

        // Solve

        struct Solver {
            static int minSol;
            static int firstSol;
            static std::vector<std::string>    solPath;

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

            static void     solveLoop(Cube& rubik);

            static size_t   getP1Length(unsigned int cornOrient, unsigned int flipUdSlice, uint8_t pruning);
            static size_t   getP2Length(unsigned int cornPerm, unsigned int edgePerm, uint8_t pruning);

            static bool     isStateUseless(const short& phase, const unsigned int& size, const P1& phase1, const P2& phase2);

            static void     generateChilds(std::set<SolvingState>& open, std::unordered_set<size_t>& close, SolvingState& current, const Cube& rubik);
            static void     solveSucess(const Cube& rubik, SolvingState& solution);
        };
};

#endif
