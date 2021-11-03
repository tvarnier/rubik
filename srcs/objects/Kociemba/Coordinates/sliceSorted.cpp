#include "../Kociemba.hpp"

static int          binomialCoeff(int n, int k)
{
    int res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

static bool         edgeIn(EDGES edge, std::array<EDGES, 4>& sliceEdges)
{ return (std::find(std::begin(sliceEdges), std::end(sliceEdges), edge) != std::end(sliceEdges)); }

static unsigned int sliceSortedCoordinates(const std::array<EDGES, 12>& edgePermutation, std::array<EDGES, 4>& sliceEdges)
{
    int             coord(0);
    int             coeff(-1);

    for (unsigned int i = 0; i < 12; ++i)
    {
        if (edgeIn(edgePermutation[i], sliceEdges))
            coeff += 1;
        else if (coeff >= 0)
        {
            coord += binomialCoeff((int)i , coeff);
        }
    }

    unsigned int    sortedCoord(0);
    unsigned int    nbr_slice(3);

    for (int i = 11; i >= 0 && nbr_slice; --i)
    {
        if (edgeIn(edgePermutation[i], sliceEdges))
        {
            unsigned int s(0);
            for (int y = i - 1; y >= 0; --y)
            {
                if (edgeIn(edgePermutation[y], sliceEdges) && edgePermutation[y] > edgePermutation[i])
                    ++s;
            }
            sortedCoord = (sortedCoord + s) * nbr_slice;
            --nbr_slice;
        }
    }

    return ((unsigned int)coord * 24 + sortedCoord);
}

std::array<EDGES, 12>   generateSliceSortedCoordinates(unsigned int coord, std::array<EDGES, 4>& sliceEdges)
{
    std::array<EDGES, 12> tmp {UR,UF,UL,UB,DR,DF,DL,DB,FR,FL,BL,BR};

    unsigned int    sortedCoord(coord % 24);

    unsigned int    nbr_slice(3);
    unsigned int    fact(6);

    for (unsigned int i = 3; i > 0; --i)
    {
        unsigned int    greater = sortedCoord / fact;
        EDGES           t = sliceEdges[i - greater];
        while (greater)
        {
            sliceEdges[i - greater] = sliceEdges[i - greater + 1];
            --greater;
        }
        sliceEdges[i] = t;
        sortedCoord %= fact;
        fact /= nbr_slice;
        nbr_slice--;
    }

    int tmpCoord(coord / 24);
    int coeff(3);

    unsigned int edge = 11;
    while (edgeIn((EDGES)edge, sliceEdges))
        --edge;
    unsigned int sliceEdge = 3;

    for (int i = 11; i >= 0 && coeff >= 0; --i)
    {
        unsigned int bc = binomialCoeff((int)i , coeff);
        if (tmpCoord >= bc)
        {
            tmpCoord -= bc;
            tmp[i] = (EDGES)edge;
            --edge;
            while (edgeIn((EDGES)edge, sliceEdges))
                --edge;
        }
        else
        {
            --coeff;
            tmp[i] = (EDGES)sliceEdges[sliceEdge];
            --sliceEdge;
        }
    }

    return (tmp);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int    Kociemba::Coord::UDSliceSorted(const std::array<EDGES, 12>& edgePermutation)
{
    std::array<EDGES, 4>   sliceEdges = { FR, FL, BL, BR };
    return (sliceSortedCoordinates(edgePermutation, sliceEdges));
}

std::array<EDGES, 12>  Kociemba::Coord::Generate::UDSliceSorted(unsigned int coord)
{
    std::array<EDGES, 4>   sliceEdges = { FR, FL, BL, BR };
    std::array<EDGES, 12> res = generateSliceSortedCoordinates(coord, sliceEdges);
    return (res);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int        Kociemba::Coord::FBSliceSorted(const std::array<EDGES, 12>& edgePermutation)
{
    std::array<EDGES, 12> tmp = Cube::multEdgePerm( Cube::multEdgePerm(Sym::Cubes[16].m_edges.p, edgePermutation), Sym::invCubes[16].m_edges.p );
    return (UDSliceSorted(tmp));
}

std::array<EDGES, 12>  Kociemba::Coord::Generate::FBSliceSorted(unsigned int coord)
{
    std::array<EDGES, 12> res = UDSliceSorted(coord);
    res = Cube::multEdgePerm( Cube::multEdgePerm(Sym::invCubes[16].m_edges.p, res), Sym::Cubes[16].m_edges.p );
    return (res);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int        Kociemba::Coord::RLSliceSorted(const std::array<EDGES, 12>& edgePermutation)
{
    std::array<EDGES, 12> tmp = Cube::multEdgePerm( Cube::multEdgePerm(Sym::invCubes[16].m_edges.p, edgePermutation), Sym::Cubes[16].m_edges.p );
    return (UDSliceSorted(tmp));
}

std::array<EDGES, 12>  Kociemba::Coord::Generate::RLSliceSorted(unsigned int coord)
{
    std::array<EDGES, 12> res = UDSliceSorted(coord);
    res = Cube::multEdgePerm( Cube::multEdgePerm(Sym::Cubes[16].m_edges.p, res), Sym::invCubes[16].m_edges.p );
    return (res);
}