#ifndef RUBIK_PROGRAM_HPP
# define RUBIK_PROGRAM_HPP

# include "rubik.hpp"
# include <memory>

# include "../Kociemba/Kociemba.hpp"
class Kociemba;

# include "../Visualizer/Visualizer.hpp"
class Visualizer;

# define SHUFFLE_DEFAULT_ITERATIONS 50

typedef struct opt {
    bool            prog = false;
    bool            visu = false;
    bool            shuffle = false;
    long int        shuffleIterations = SHUFFLE_DEFAULT_ITERATIONS;
    std::vector<string> moves = {};
} RubikProgramOptions;
    
class   RubikProgram
{
    public:
        RubikProgram(int ac, char **av);

    private:
        Cube            c;
        Kociemba        k;
        Visualizer*     v;
        std::thread*    visuThread;

        void        init();
        int         parsing(int ac, char **av, RubikProgramOptions& options);
};

// -v visu      -s n SHUFFLE  

#endif