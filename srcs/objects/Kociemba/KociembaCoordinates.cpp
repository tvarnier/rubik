# include "Kociemba.hpp"

unsigned int        Kociemba::cornerOrientationCoordinates(const std::array<unsigned int, 8>& cornerOrientation)
{
    unsigned int modulo = 729;

    unsigned int coord = 0;
    
    for ( unsigned int i = 0; i < 7; ++i)
    {
        coord += cornerOrientation[i] * modulo;
        modulo /= 3;
    }
    return (coord);
}

std::array<unsigned int, 8> Kociemba::generateCornerOrientation(unsigned int coord)
{
    std::array<unsigned int, 8> tmp = {};

    unsigned int modulo = 1;

    unsigned int total = 0;

    for (int i = 6; i >= 0; --i)
    {
        tmp[i] = (coord / modulo) % 3;
        total += tmp[i];
        modulo *= 3;
    }
    if (total % 3)
        tmp[7] = 3 - (total % 3);

    if (coord != cornerOrientationCoordinates(tmp))
    {
        printf("\n\n  %u : ERROR | \n\n", coord);
    }

    return (tmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int        Kociemba::cornerPermutationCoordinates(const std::array<CORNERS, 8>& cornerPermutation)
{
    unsigned int fact = 1;
    unsigned int coord = 0;
    for (unsigned int i = 1; i < 8; ++i)
    {
        fact *= i;
        for (unsigned int y = 0; y < i; ++y)
            if (cornerPermutation[i] < cornerPermutation[y])
                coord += fact;
    }
    return (coord);
}

std::array<CORNERS, 8>  Kociemba::generateCornerPermutation(unsigned int coord)
{
    std::array<CORNERS, 8> tmp {URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB};

    unsigned int fact = 5040;
    for (unsigned int i = 7; i > 0; --i)
    {
        unsigned int greater = (coord % (fact * (i + 1))) / fact;
        CORNERS     t = tmp[i - greater];
        while (greater)
        {
            tmp[i - greater] = tmp[i - greater + 1];
            --greater;
        }
        tmp[i] = t;
        fact /= i;
    }

    return (tmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int        Kociemba::edgeOrientationCoordinates(const std::array<unsigned int, 12>& edgeOrientation)
{
    unsigned int modulo = 1024;

    unsigned int coord = 0;
    
    for ( unsigned int i = 0; i < 11; ++i)
    {
        coord += edgeOrientation[i] * modulo;
        modulo /= 2;
    }
    return (coord);
}

std::array<unsigned int, 12> Kociemba::generateEdgeOrientation(unsigned int coord)
{
    std::array<unsigned int, 12> tmp = {};

    unsigned int modulo = 1;
    unsigned int total = 0;

    for (int i = 10; i >= 0; --i)
    {
        tmp[i] = (coord / modulo) % 2;
        total += tmp[i];
        modulo *= 2;
    }
    if (total % 2)
        tmp[11] = 2 - (total % 2);
    return (tmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int        Kociemba::edgePermutationCoordinates(const std::array<EDGES, 12>& edgePermutation)
{
    unsigned int fact = 1;
    unsigned int coord = 0;
    for (unsigned int i = 1; i < 12; ++i)
    {
        fact *= i;
        for (unsigned int y = 0; y < i; ++y)
            if (edgePermutation[i] < edgePermutation[y])
                coord += fact;
    }
    return (coord);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int        Kociemba::phase2EdgePermutationCoordinates(const std::array<EDGES, 12>& edgePermutation)
{
    unsigned int fact = 1;
    unsigned int coord = 0;
    for (unsigned int i = 1; i < 8; ++i)
    {
        fact *= i;
        for (unsigned int y = 0; y < i; ++y)
            if (edgePermutation[i] < edgePermutation[y])
                coord += fact;
    }
    return (coord);
}

std::array<EDGES, 12>  Kociemba::generateP2EdgePermutation(unsigned int coord)
{
    std::array<EDGES, 12> tmp {UR,UF,UL,UB,DR,DF,DL,DB,FR,FL,BL,BR};

    unsigned int fact = 5040;
    for (unsigned int i = 7; i > 0; --i)
    {
        unsigned int    greater = (coord % (fact * (i + 1))) / fact;
        EDGES           t = tmp[i - greater];
        while (greater)
        {
            tmp[i - greater] = tmp[i - greater + 1];
            --greater;
        }
        tmp[i] = t;
        fact /= i;
    }

    return (tmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int          binomialCoeff(int n, int k)
{
    // if (k > n)
    //     return 0;
    // if (k == 0 || k == n)
    //     return 1;
    // return binomialCoeff(n - 1, k - 1)
    //        + binomialCoeff(n - 1, k);

    int res = 1;
 
    // Since C(n, k) = C(n, n-k)
    if (k > n - k)
        k = n - k;
 
    // Calculate value of
    // [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1]
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
 
    return res;
}

unsigned int        Kociemba::UDSliceCoordinates(const std::array<EDGES, 12>& edgePermutation)
{
    int             coord(0);
    int             coeff(-1);

    for (unsigned int i = 0; i < 12; ++i)
    {
        if (edgePermutation[i] >= FR)
            coeff += 1;
        else if (coeff >= 0)
        {
            coord += binomialCoeff((int)i , coeff);
        }
    }

    return ((unsigned int)coord);
}

std::array<EDGES, 12>   Kociemba::generateUDSlice(unsigned int coord)
{
    std::array<EDGES, 12> tmp {UR,UF,UL,UB,DR,DF,DL,DB,FR,FL,BL,BR};
    int coeff((( coord >= binomialCoeff(11 , 3)) ? 3 : 2));
    int tmpCoord(coord);

    unsigned int edge = (unsigned int)7;
    unsigned int sliceEdge = (unsigned int)11 - (3 - coeff);

    for (int i = 11 - (3 - coeff); i >= 0 && coeff >= 0; --i)
    {
        unsigned int bc = binomialCoeff((int)i , coeff);
        if (tmpCoord >= bc)
        {
            tmpCoord -= bc;
            tmp[i] = (EDGES)edge;
            --edge;
        }
        else
        {
            --coeff;
            tmp[i] = (EDGES)sliceEdge;
            --sliceEdge;
        }
    }

    return tmp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int        Kociemba::UDSliceSortedCoordinates(const std::array<EDGES, 12>& edgePermutation)
{
    unsigned int    coord(0);
    unsigned int    nbr_slice(3);

    for (int i = 11; i >= 0 && nbr_slice; --i)
    {
        if (edgePermutation[i] >= FR)
        {
            unsigned int s(0);
            for (int y = i - 1; y >= 0; --y)
            {
                if (edgePermutation[y] >= FR && edgePermutation[y] > edgePermutation[i])
                    ++s;
            }
            coord = (coord + s) * nbr_slice;
            --nbr_slice;
        }
    }

    return (coord);
}

std::array<EDGES, 12>  Kociemba::generateUDSliceSorted(unsigned int coord)
{
    std::array<EDGES, 12> tmp {UR,UF,UL,UB,DR,DF,DL,DB,FR,FL,BL,BR};

    unsigned int    nbr_slice(3);
    unsigned int    fact(6);

    for (unsigned int i = 11; i > 8; --i)
    {
        unsigned int    greater = coord / fact;
        EDGES           t = tmp[i - greater];
        while (greater)
        {
            tmp[i - greater] = tmp[i - greater + 1];
            --greater;
        }
        tmp[i] = t;
        coord %= fact;
        fact /= nbr_slice;
        nbr_slice--;
    }

    return (tmp);
}