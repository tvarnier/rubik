#include "rubik.hpp"

int		main(int ac, char **av)
{
	Cube rubik;

	if (ac >= 2)
	{
		for (int i = 1; i < ac; ++i)
			if (rubik.parseAndMove(av[i]))
				return (1);
		rubik.print();
	}
	return (0);
}