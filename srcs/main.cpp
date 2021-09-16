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

	// std::string moves = "R L' D' U' R2 F2 D";//R U D'";

	// std::vector<string> el = {};
	// split(std::string(moves), ' ', el);

	// for (auto it = el.begin(); it != el.end(); ++it)
	// 	rubik.move(*it);

	rubik.shuffle(1);

	// rubik.move("B'");
	// rubik.move("F'");
	// rubik.move("D'");

	k.solve(rubik);

	return (0);
}