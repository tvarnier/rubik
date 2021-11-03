#include "Kociemba.hpp"

char Kociemba::PruneTable::P1[35227103] = {};
char Kociemba::PruneTable::P2_CPEP[27901440] = {};

std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::CornerOrientation = {};
std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::EdgeOrientation   = {};
std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::UDSlice           = {};
std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::FlipUDSlice       = {};

std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::UDSliceSorted     = {};
std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::FBSliceSorted     = {};
std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::RLSliceSorted     = {};

std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::CornerPermutation = {};
std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::P2EdgePermutation = {};
std::vector< std::array<unsigned int, 18> > Kociemba::MoveTable::P2UDSlice         = {};

std::vector< std::array<unsigned int, 24> > Kociemba::MoveTable::edge8Perm = {};


std::array< Cube, 48 > Kociemba::Sym::Cubes = {};
std::array< Cube, 48 > Kociemba::Sym::invCubes = {};

std::vector< std::array<unsigned int, 16> > Kociemba::Sym::MoveTable::P2EdgePermutation = {};
std::vector< std::array<unsigned int, 16> > Kociemba::Sym::MoveTable::cornerOrientation = {};

std::vector< unsigned int >    Kociemba::Sym::Rep::cornerPermutation = {};
std::vector< unsigned int >    Kociemba::Sym::Rep::FlipUDSlice = {};

std::vector< std::pair< unsigned int, std::vector<unsigned int> > > Kociemba::Sym::RepTable::cornerPermutation = {};
std::vector< std::pair< unsigned int, std::vector<unsigned int> > > Kociemba::Sym::RepTable::FlipUDSlice = {};

std::vector< unsigned int >                  Kociemba::DephtTable::CornerPermutation;

int     Kociemba::init()
{
    if (Sym::Generate::all())
        return (1);
    if (MoveTable::Generate::all())
        return(1);
    if (PruneTable::Generate::all())
        return(1);
    DephtTable::Generate::all();

    return (0);
}

int     Kociemba::Sym::Generate::all()
{
    Sym::MoveTable::P2EdgePermutation.resize(40320);
    Sym::MoveTable::cornerOrientation.resize(2187);

    Sym::Rep::cornerPermutation.resize(2768);
    Sym::Rep::FlipUDSlice.resize(64430 );
    
    Sym::RepTable::cornerPermutation.resize(CORNER_PERMUTATION_MOVETABLE_SIZE);
    Sym::RepTable::FlipUDSlice.resize(FLIP_UD_SLICE_MOVETABLE_SIZE);

    Sym::Generate::Cubes();
    Sym::Generate::invCubes();

    Sym::MoveTable::Generate::cornerOrientation();
    Sym::MoveTable::Generate::P2EdgePermutation();

    if (Sym::Rep::Generate::FlipUDSlice())
        return (1);
    Sym::RepTable::Generate::FlipUDSlice();
    Sym::RepTable::Generate::generate_CornerPermutationSym_MoveTable();
    return (0);
}

int     Kociemba::MoveTable::Generate::all()
{
    MoveTable::CornerOrientation.resize(CORNER_ORIENTATION_MOVETABLE_SIZE);
    MoveTable::EdgeOrientation.resize(EDGE_ORIENTATION_MOVETABLE_SIZE);
    MoveTable::UDSlice.resize(UD_SLICE_MOVETABLE_SIZE);
    MoveTable::FlipUDSlice.resize(FLIP_UD_SLICE_MOVETABLE_SIZE);

    MoveTable::UDSliceSorted.resize(UD_SLICE_SORTED_MOVETABLE_SIZE);
    MoveTable::FBSliceSorted.resize(UD_SLICE_SORTED_MOVETABLE_SIZE);
    MoveTable::RLSliceSorted.resize(UD_SLICE_SORTED_MOVETABLE_SIZE);

    MoveTable::CornerPermutation.resize(CORNER_PERMUTATION_MOVETABLE_SIZE);
    MoveTable::P2EdgePermutation.resize(P2_EDGE_PERMUTATION_MOVETABLE_SIZE);
    MoveTable::P2UDSlice.resize(P2_UD_SLICE_MOVETABLE_SIZE);

    MoveTable::edge8Perm.resize(11880);
    
    MoveTable::Generate::CornerOrientation();
    MoveTable::Generate::EdgeOrientation();
    MoveTable::Generate::UDSlice();
    MoveTable::Generate::FlipUDSlice();

    MoveTable::Generate::UDSliceSorted();
    MoveTable::Generate::FBSliceSorted();
    MoveTable::Generate::RLSliceSorted();

    MoveTable::Generate::CornerPermutation();
    MoveTable::Generate::P2EdgePermutation();
    MoveTable::Generate::P2UDSlice();

    MoveTable::Generate::Edge8Perm();

    return (0);
}

void    Kociemba::DephtTable::Generate::all()
{
    DephtTable::CornerPermutation.resize(CORNER_PERMUTATION_MOVETABLE_SIZE);
    Kociemba::DephtTable::Generate::one(
        Kociemba::DephtTable::CornerPermutation,
        Kociemba::MoveTable::CornerPermutation,
        18
    );
}