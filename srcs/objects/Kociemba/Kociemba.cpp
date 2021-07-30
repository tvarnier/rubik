#include "Kociemba.hpp"

char Kociemba::P1_COEO_PruneTable[1119744] = {};
char Kociemba::P1_COUS_PruneTable[270642] = {};
char Kociemba::P1_USEO_PruneTable[253440] = {};

char Kociemba::P2_CPEP_PruneTable[406425600] = {};
char Kociemba::P2_CPUS_PruneTable[241920] = {};
char Kociemba::P2_USEP_PruneTable[241920] = {};

Kociemba::Kociemba() {
    generate_moveTables();
    generate_pruneTables();
}