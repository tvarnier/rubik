#include "Kociemba.hpp"

char Kociemba::P1_PruneTable[35227103] = {};
char Kociemba::P2_CPEP_PruneTable[27901440] = {};

std::vector< std::array<unsigned int, 18> > Kociemba::CornerOrientation_MoveTable = {};
std::vector< std::array<unsigned int, 18> > Kociemba::EdgeOrientation_MoveTable   = {};
std::vector< std::array<unsigned int, 18> > Kociemba::UDSlice_MoveTable           = {};
std::vector< std::array<unsigned int, 18> > Kociemba::FlipUDSlice_MoveTable       = {};

std::vector< std::array<unsigned int, 18> > Kociemba::UDSliceSorted_MoveTable     = {};
std::vector< std::array<unsigned int, 18> > Kociemba::FBSliceSorted_MoveTable     = {};
std::vector< std::array<unsigned int, 18> > Kociemba::RLSliceSorted_MoveTable     = {};

std::vector< std::array<unsigned int, 18> > Kociemba::CornerPermutation_MoveTable = {};
std::vector< std::array<unsigned int, 18> > Kociemba::P2EdgePermutation_MoveTable = {};
std::vector< std::array<unsigned int, 18> > Kociemba::P2UDSlice_MoveTable         = {};

std::vector< std::array<unsigned int, 24> > Kociemba::edge8Perm = {};

std::vector< unsigned int >    Kociemba::CornPerm_SymRep = {};
std::vector< std::pair< unsigned int, std::vector<unsigned int> > > Kociemba::CornPerm_Sym = {};

std::vector< unsigned int >    Kociemba::FlipUDSlice_SymRep = {};
std::vector< std::pair< unsigned int, std::vector<unsigned int> > > Kociemba::FlipUDSlice_Sym = {};

std::vector< std::array<unsigned int, 16> > Kociemba::P2EdgePermSym_MoveTable = {};
std::vector< std::array<unsigned int, 16> > Kociemba::CornOrientSym_MoveTable = {};

std::vector< unsigned int >                  Kociemba::CornerPermutation_DephtTable;

std::array< Cube, 48 > Kociemba::symCubes = {};
std::array< Cube, 48 > Kociemba::symInvCubes = {};

void    Kociemba::initContainers() {
    Kociemba::CornerOrientation_MoveTable.resize(CORNER_ORIENTATION_MOVETABLE_SIZE);
    Kociemba::EdgeOrientation_MoveTable.resize(EDGE_ORIENTATION_MOVETABLE_SIZE);
    Kociemba::UDSlice_MoveTable.resize(UD_SLICE_MOVETABLE_SIZE);
    Kociemba::FlipUDSlice_MoveTable.resize(FLIP_UD_SLICE_MOVETABLE_SIZE);

    Kociemba::UDSliceSorted_MoveTable.resize(UD_SLICE_SORTED_MOVETABLE_SIZE);
    Kociemba::FBSliceSorted_MoveTable.resize(UD_SLICE_SORTED_MOVETABLE_SIZE);
    Kociemba::RLSliceSorted_MoveTable.resize(UD_SLICE_SORTED_MOVETABLE_SIZE);

    Kociemba::CornerPermutation_MoveTable.resize(CORNER_PERMUTATION_MOVETABLE_SIZE);
    Kociemba::P2EdgePermutation_MoveTable.resize(P2_EDGE_PERMUTATION_MOVETABLE_SIZE);
    Kociemba::P2UDSlice_MoveTable.resize(P2_UD_SLICE_MOVETABLE_SIZE);

    Kociemba::edge8Perm.resize(11880);

    Kociemba::CornPerm_SymRep.resize(2768);
    Kociemba::CornPerm_Sym.resize(CORNER_PERMUTATION_MOVETABLE_SIZE);

    Kociemba::FlipUDSlice_SymRep.resize(64430 );
    Kociemba::FlipUDSlice_Sym.resize(FLIP_UD_SLICE_MOVETABLE_SIZE);

    Kociemba::P2EdgePermSym_MoveTable.resize(40320);
    Kociemba::CornOrientSym_MoveTable.resize(2187);
    
    Kociemba::CornerPermutation_DephtTable.resize(CORNER_PERMUTATION_MOVETABLE_SIZE);
}

int     Kociemba::init()
{
    initContainers();

    generate_symmetries();
    if (generate_moveTables())
        return(1);
    if (generate_pruneTables())
        return(1);
    generate_dephtTables();

    return (0);
}