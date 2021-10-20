#ifndef CUBE_HPP
# define CUBE_HPP

# include <string>
# include <iostream>
# include <limits>
# include <iterator>
# include <sstream>
# include <algorithm>
# include <set>
# include <unordered_map>
# include <map>
# include <array>
# include <functional>
# include <regex>
# include <array>
# include <cmath>
# include <list>
# include <fstream>
# include <iomanip>
# include <queue>

enum CORNERS : unsigned int {URF=0,UFL=1,ULB=2,UBR=3,DFR=4,DLF=5,DBL=6,DRB=7};
enum EDGES : unsigned int {UR=0,UF=1,UL=2,UB=3,DR=4,DF=5,DL=6,DB=7,FR=8,FL=9,BL=10,BR=11};

# define ROT_UP     0
# define ROT_RIGHT  1
# define ROT_FRONT  2
# define ROT_DOWN   3
# define ROT_LEFT   4
# define ROT_BACK   5

# define ROT_URF3   6
# define ROT_F2     7
# define ROT_U4     8
# define ROT_LR2    9

struct corners {
    std::array<CORNERS, 8>          p;
    std::array<unsigned int, 8>     o;
    corners() 
    {
        for ( CORNERS i = URF; i < 8; i = (CORNERS) ((unsigned int)i + 1) )
        { p[i] = i; o[i] = 0; }
    }
};

struct edges {
    std::array<EDGES, 12>           p;
    std::array<unsigned int, 12>    o;
    edges() 
    {
        for ( EDGES i = UR; i < 12; i = (EDGES) ((unsigned int)i + 1) )
        { p[i] = i; o[i] = 0; }
    }
};

class Cube
{
    public:
        corners     m_corners;
        edges       m_edges;

        Cube();

        int             move(const std::string m);
        static bool     isMove(const std::string m);
        void            shuffle(int iterations = 100);

        void                            rotation(const unsigned int& rot);
        
        static std::array<CORNERS, 8>   rotateCornPerm(const std::array<CORNERS, 8>& cornPerm, const unsigned int& rot);
        static std::array<unsigned int, 8>  rotateCornOrient(const std::array<unsigned int, 8>& cornOrient, const unsigned int& rot);
        
        static edges                    rotateEdges(const edges& edgeCoord, const unsigned int& rot);
        static std::array<EDGES, 12>    rotateEdgePerm(const std::array<EDGES, 12>& edgePerm, const unsigned int& rot);
        static std::array<unsigned int, 12> rotateEdgeOrient(const std::array<unsigned int, 12>& edgeOrient, const unsigned int& rot);

        static Cube                     multCube(const Cube& first, const Cube& second);

        static corners                  multCorners(const corners& first, const corners& second);
        static std::array<CORNERS, 8>   multCornPerm(const std::array<CORNERS, 8>& first, const std::array<CORNERS, 8>& second);
        static edges                    multEdges(const edges& first, const edges& second);
        static std::array<EDGES,  12>   multEdgePerm(const std::array<EDGES, 12>& first, const std::array<EDGES, 12>& second);

        Cube&           operator=(const Cube& other);

    private:
        typedef void (Cube::*moveFunction)(void);
        static std::map<std::string, moveFunction>              moveMap;

        void            up();
        void            upR();
        void            up2();
        void            down();
        void            downR();
        void            down2();

        void            right();
        void            rightR();
        void            right2();
        void            left();
        void            leftR();
        void            left2();

        void            front();
        void            frontR();
        void            front2();
        void            back();
        void            backR();
        void            back2();
};

#endif