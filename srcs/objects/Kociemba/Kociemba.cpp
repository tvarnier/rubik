#include "Kociemba.hpp"

char Kociemba::P2_CPEP_PruneTable[406425600] = {};
char Kociemba::P2_CPUS_PruneTable[241920] = {};
char Kociemba::P2_USEP_PruneTable[241920] = {};


Kociemba::Kociemba() {
    generate_moveTables();
    generate_pruneTables();
}