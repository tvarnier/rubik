#include "Kociemba.hpp"

char Kociemba::P1_PruneTable[35227103] = {};
char Kociemba::P2_PruneTable[27901440] = {};

std::vector< std::array<unsigned int, 16> > Kociemba::P2EdgePermSym_MoveTable = {};
std::vector< std::array<unsigned int, 16> > Kociemba::CornOrientSym_MoveTable = {};


// char Kociemba::P1_COEO_PruneTable[1119744] = {};
// char Kociemba::P1_COUS_PruneTable[270642] = {};
// char Kociemba::P1_USEO_PruneTable[253440] = {};

// char Kociemba::P2_CPEP_PruneTable[406425600] = {};
// char Kociemba::P2_CPUS_PruneTable[241920] = {};
// char Kociemba::P2_USEP_PruneTable[241920] = {};

// std::array< std::array<unsigned int, 18>,  CORNER_ORIENTATION_MOVETABLE_SIZE > Kociemba::CornerOrientation_MoveTable = {};
// std::array< std::array<unsigned int, 18>,    EDGE_ORIENTATION_MOVETABLE_SIZE > Kociemba::EdgeOrientation_MoveTable = {};
// std::array< std::array<unsigned int, 18>,            UD_SLICE_MOVETABLE_SIZE > Kociemba::UdSlice_MoveTable = {};

// std::array< std::array<unsigned int, 18>,  CORNER_PERMUTATION_MOVETABLE_SIZE >  CornerPermutation_MoveTable = {};
// std::array< std::array<unsigned int, 18>, P2_EDGE_PERMUTATION_MOVETABLE_SIZE >  P2EdgePermutation_MoveTable = {};
// std::array< std::array<unsigned int, 18>,     UD_SLICE_SORTED_MOVETABLE_SIZE >  UdSliceSorted_MoveTable = {};

// std::array< unsigned int,  CORNER_PERMUTATION_MOVETABLE_SIZE >                  CornerPermutation_DephtTable = {};
// std::array< unsigned int, P2_EDGE_PERMUTATION_MOVETABLE_SIZE >                  EdgePermutation_DephtTable = {};
// std::array< unsigned int,     UD_SLICE_SORTED_MOVETABLE_SIZE >                  UdSliceSorted_DephtTable = {};

// std::array< Cube, 16 >    symCubes = {};
// std::array< Cube, 16 > symInvCubes = {};


// std::array< std::array<unsigned int, 18>, 2768>  CornPermSym_MoveTable = {};
// std::array< unsigned int, 2768 >    CornSymRep = {};
// std::array< std::pair< unsigned int, std::vector<unsigned int> >, CORNER_PERMUTATION_MOVETABLE_SIZE >    CornSym = {};

Kociemba::Kociemba() {
    generate_symmetries();
    generate_moveTables();
    generate_pruneTables();
    // generate_dephtTables();
}