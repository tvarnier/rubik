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

	/*std::string moves = "R2 F2 B2 F2 B2 D' L2 D' L2 F2 U2 R2 F2 B2 F2 D2 R2 F2 D2 F2 L2 U F2 D R2 L2 D R2 U F2 D' R2 L2 D R2 L2 F2 R2 D' F2 B2 L2 F2 B2 F2 R2 L2 R2 D2 F2 U D2 R2 U' D R2 U2 R2 L2 D2 F2 B2 D2 R2 D2 U' F2 U' R2 L2 U' D2 R2 L2 D2 L2 R2 L2 F2 R2 F2 D2 L2 U' L2 F2 U2 F2 R2 D2 U D2 L2 R2 D2 U2 R2 D' U' F2";

	std::vector<string> el = {};
	split(moves, ' ', el);

	for (auto it = el.begin(); it != el.end(); ++it)
		rubik.move(*it);*/

	rubik.shuffle(10);

	k.solve(rubik);

	return (0);
}