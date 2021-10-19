#ifndef RUBIK_PROGRAM_HPP
# define RUBIK_PROGRAM_HPP

# include "rubik.hpp"

# include "../Kociemba/Kociemba.hpp"
class Kociemba;

# include "../Visualizer/Visualizer.hpp"
class Visualizer;


class   RubikProgram
{
    public:
        RubikProgram(int ac, char **av);

    private:
        Cube          c;
        Kociemba      k;
        Visualizer*   v;
        struct options {
            bool            visu = false;
            unsigned int    shuffleIterations= 100;
        } options;

        void        init();
        void        parseOptions();
};

// -v visu      -s n SHUFFLE  

#endif