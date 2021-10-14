#include "rubik.hpp"

void split(const string &chaine, char delimiteur, std::vector<string> &elements)
{
	stringstream ss(chaine);
	string sousChaine;
	while (getline(ss, sousChaine, delimiteur))
	{
		elements.push_back(sousChaine);
	}
}

int		main(int ac, char **av)
{
	Visualizer v(1920, 1080);

    v.draw();
    return 0;
	/*Kociemba k;
	Cube	 rubik;

	
	// F R' L U2 R2 L2

	// F B L D2 R2 D2

	if (ac == 2)
	{
		std::string moves = av[1];
		std::vector<string> el = {};
		split(std::string(moves), ' ', el);

		for (auto it = el.begin(); it != el.end(); ++it)
			rubik.move(*it);
	}
	else
		rubik.shuffle(15);

	k.solve(rubik);*/

	return (0);
}

// U R2 F B R B2 R U2 L B2 R U' D' R2 F R' L B2 U2 F2

// B  D' F' L2 U2 F' R2 D2 R' F  U' L' F' R2 U  L2 D2 F2 R2 D'

// R' D R' D F B R2 U R' D R' L' U'

// B' F' U2 L2 D' U2

// L2 D' R F2 U2 L' R' D2 R2 L'

// B2 R2 F2 R D2 R' F' L U2 D

// D L F2 R2 L2 F' D2 R

// R' D2 B2 F L' F2 R2 L2 B2 D'


// U2 D' R' F' B D U' D F' B

// D L' U R2 U' D' F2 B2 R' L2