# include "RubikProgram.hpp"

RubikProgram::RubikProgram(int ac, char **av) {
    if (ac > 1)
        ;
    else
    {
        c.shuffle(50);
        k.solve(c);
    }
}

void    RubikProgram::parseOptions(int ac, char **av)
{
    for (int i = 1; i < ac; ++ac)
    {
        if (string(av[i]) == "-v")
            options.visu = true;
        else if (string(av[i]) == "-s")
        {
            if (i + 1 >= ac)
            {
                printf();
                return ;
            }
        }
    }
}