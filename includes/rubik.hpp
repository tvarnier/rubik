#ifndef RUBIK_HPP
# define RUBIK_HPP

# include "../srcs/objects/Kociemba/Kociemba.hpp"
class Kociemba;

# include "../srcs/objects/Visualizer/Visualizer.hpp"
class Visualizer;

# define SHUFFLE_DEFAULT_ITERATIONS 30

typedef struct opt {
    bool            prog = false;
    bool            visu = false;
    bool            shuffle = false;
    long int        shuffleIterations = SHUFFLE_DEFAULT_ITERATIONS;
    std::vector<std::string> moves = {};
} RubikOptions;
    
int         parsing(int ac, char **av, RubikOptions& options);

#endif