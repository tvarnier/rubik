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
        modulo /= 3;
    }
    return (coord);
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
    if (k > n)
        return 0;
    if (k == 0 || k == n)
        return 1;
    return binomialCoeff(n - 1, k - 1)
           + binomialCoeff(n - 1, k);
}

unsigned int        Kociemba::UDSliceCoordinates(const std::array<EDGES, 12>& edgePermutation)
{
    int             coord(0);
    bool            first(false);
    int             coeff(-1);

    for (unsigned int i = 1; i < 12; ++i)
    {
        if (edgePermutation[i] >= FR)
            coeff += 1;
        else if (coeff >= 0)
            coord += binomialCoeff((int)i , coeff);
    }

    return ((unsigned int)coord);
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