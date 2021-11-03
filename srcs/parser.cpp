#include "rubik.hpp"

void split(const std::string &chaine, char delimiteur, std::vector<std::string> &elements)
{
	std::stringstream ss(chaine);
	std::string sousChaine;
	while (getline(ss, sousChaine, delimiteur))
	{
		elements.push_back(sousChaine);
	}
}

static bool     is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int     parsing(int ac, char **av, RubikOptions& options)
{
    for (int i = 1; i < ac; ++i)
    {
        if (std::string(av[i]) == "-v")
            options.visu = true;
        else if (std::string(av[i]) == "-s")
        {
            if (!options.moves.empty()) { std::fprintf(stderr, "Error: Shuffle or specific Moves, not both.\n"); return (1); }
            options.shuffle = true;
            if (i + 1 < ac && is_number(av[i + 1]))
            {
                options.shuffleIterations = strtol(av[i + 1], NULL, 10);
                if (options.shuffleIterations < 0 || options.shuffleIterations > 100) { std::fprintf(stderr, "Error: 0 >= ShuffleIterations <= 100.\n"); return (1); }
                ++i;
            }
        }
        else
        {
            split(av[i], ' ', options.moves);
            for (auto& it: options.moves)
                if (!Cube::isMove(it)) { std::fprintf(stderr, "Error: '%s' is not a valid Move.\n", it.c_str()); return (1); }
            if (options.shuffle) { std::fprintf(stderr, "Error: Shuffle or Specific Moves, not both.\n"); return (1); }  
        }
    }
    return (0);
}