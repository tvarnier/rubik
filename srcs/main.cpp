#include "rubik.hpp"

int		main(int ac, char **av)
{
	Kociemba k;
	Cube	 rubik;

	k.generate_moveTables();
	k.generate_Dephts();

	/*if (ac >= 2)
	{
		for (int i = 1; i < ac; ++i)
			if (rubik.parseAndMove(av[i]))
				return (1);
	}
	else
		rubik.shuffle(10);*/
	rubik.shuffle(10);

	k.solve(rubik);

	/*lib::printendl("Corner Orientation  : ", rubik.cornerOrientationCoordinates());
	lib::printendl("Corner Permutation  : ", rubik.cornerPermutationCoordinates());
	lib::printendl("Edge Orientation    : ", rubik.edgeOrientationCoordinates());
	lib::printendl("Edge Permutation    : ", rubik.edgePermutationCoordinates());
	lib::printendl("P2 Edge Permutation : ", rubik.phase2EdgePermutationCoordinates());
	lib::printendl("UD Slice            : ", rubik.UDSliceCoordinates());
	lib::printendl("UD Slice Sorted     : ", rubik.UDSliceSortedCoordinates());*/

	return (0);
}