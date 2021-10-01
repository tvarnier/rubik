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
	Kociemba k;
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
		rubik.shuffle(10);

	k.solve(rubik);

	return (0);
}

// D L F2 R2 L2 F' D2 R

// R' D2 B2 F L' F2 R2 L2 B2 D'