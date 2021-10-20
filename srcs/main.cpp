#include "rubik.hpp"

int		main(int ac, char **av)
{
	RubikProgram	R(ac, av);
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

// D R L F L2 F' D2 R' L F'