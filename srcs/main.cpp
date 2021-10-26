#include "rubik.hpp"

static void	printMoves(std::string prefix, std::vector<std::string>& moves, bool isVisu, Visualizer* v)
{
	printf("%s (%2lu) : ", prefix.c_str(), moves.size());
	for (auto& m: moves)
	{
		printf("%s ", m.c_str());
		if (isVisu)
			v->moveQueue.emplace(m);
	}
	printf("\n");
	if (isVisu)
		v->drawLoop();
}

int		main(int ac, char **av)
{
	RubikOptions options;
	int			ret = 0;

    options.moves.clear();

    if (parsing(ac, av, options))
        return (1);

    Cube        c;
    Visualizer* v = NULL;

    if (options.visu)
    {
        v = new Visualizer(1080, 1080);
        v->draw();
    }

    if (options.moves.empty())
		options.moves = c.shuffle(options.shuffleIterations);
	else
		for (auto& m: options.moves)
			c.move(m);
	printMoves(std::string("MIX"), options.moves, options.visu, v);

	if (!(ret = Kociemba::init()))
	{
		std::vector<std::string> solPath = Kociemba::solve(c);
		printMoves(std::string("SOL"), solPath, options.visu, v);
		solPath.clear();
	}

    if (v != NULL)
        delete(v);

	return (ret);
}