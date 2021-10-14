#include "Kociemba.hpp"

char Kociemba::P1_PruneTable[35227103] = {};
char Kociemba::P2_CPEP_PruneTable[27901440] = {};
char Kociemba::P2_CPUS_PruneTable[241920] = {};
char Kociemba::P2_USEP_PruneTable[241920] = {};

std::vector< std::array<unsigned int, 16> > Kociemba::P2EdgePermSym_MoveTable = {};
std::vector< std::array<unsigned int, 16> > Kociemba::CornOrientSym_MoveTable = {};

Kociemba::Kociemba() {
    generate_symmetries();
    generate_moveTables();
    generate_pruneTables();
    generate_dephtTables();
}