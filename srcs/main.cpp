#include "rubik.hpp"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	Cube rubik;

	rubik.print();
	
	rubik.front();
	rubik.right();
	rubik.up2();
	rubik.backR();
	rubik.leftR();
	rubik.downR();

	rubik.print();

	return (0);
}