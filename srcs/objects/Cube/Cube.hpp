#ifndef CUBE_HPP
# define CUBE_HPP

# include "rubik.hpp"

# define UP     0
# define LEFT   1
# define FRONT  2
# define RIGHT  3
# define BACK   4
# define DOWN   5

# define UL     0
# define U      1
# define UR     2
# define R      3
# define DR     4
# define D      5
# define DL     6
# define L      7

/**
   * A raw Rubik's Cube model.  This is _not_ what is drawn.  It's a fairly
   * fast Rubik's Cube model used by the solver, and kept in sync with the
   * drawable Rubik's Cube WorldObject.
   *
   * The cube is laid out as follows.
   *
   * The sides:
   *
   *    U
   *  L F R B
   *    D
   *
   * Color wise:
   *
   *          W W W
   *          W W W
   *          W W W
   *
   *  G G G   R R R   B B B   O O O
   *  G G G   R R R   B B B   O O O
   *  G G G   R R R   B B B   O O O
   *
   *          Y Y Y
   *          Y Y Y
   *          Y Y Y
   *
   * Index wise:
   *
   *
   *              0  1  2
   *              7     3
   *              6  5  4
   *
   *   8  9 10   16 17 18   24 25 26   32 33 34
   *  15    11   23    19   31    27   39    35
   *  14 13 12   22 21 20   30 29 28   38 37 36
   *
   *             40 41 42
   *             47    43
   *             46 45 44
   *
   * Centers:
   *
   *    0
   *  1 2 3 4
   *    5
   */



class Cube {

    public :
        Cube();					    // Constructor
		Cube(const Cube& other);	// Constructor

        enum class  COLOR {CWHITE, CGREEN, CRED, CBLUE, CORANGE, CYELLOW};

        void        print();

        /*     Movements     */

        void        up();
        void        upR();
        void        up2();
        void        down();
        void        downR();
        void        down2();

        void        right();
        void        rightR();
        void        right2();
        void        left();
        void        leftR();
        void        left2();

        void        front();
        void        frontR();
        void        front2();
        void        back();
        void        backR();
        void        back2();

    private :
        std::array<int, 6>  m_cube;
        std::array<int, 6>  m_center;

        void            getColor(COLOR color);
        int             getColorFromIndex(int face, int x, int y);
        int             getColorFromPos(int face, int pos);

        void            invert(int op1[4], int op2[4], int op3[4], int op4[4]);

        std::array<int, 3>   getValuesCubie(int op[4]);
        std::array<int, 3>   swapCubie(int op[4], std::array<int, 3> replacer);
        

        // Rotations


};

#endif