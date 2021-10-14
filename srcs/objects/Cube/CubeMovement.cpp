#include "Cube.hpp"

const std::array< std::array< CORNERS,  8 >, 10 >   CornerCubieMovePosition =
{{
    { UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB },     // U
    { DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR },     // R
    { UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB },     // F
    { URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR },     // D
    { URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB },     // L
    { URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL },     // B
    { URF, DFR, DLF, UFL, UBR, DRB, DBL, ULB },     // ROT_URF3
    { DLF, DFR, DRB, DBL, UFL, URF, UBR, ULB },     // ROT_F2
    { UBR, URF, UFL, ULB, DRB, DFR, DLF, DBL },     // ROT_U4
    { UFL, URF, UBR, ULB, DLF, DFR, DRB, DBL }      // ROT_LR2
}};
const std::array< std::array< unsigned int,  8 >, 10 >  CornerCubieMoveOrientation =
{{
    { 0, 0, 0, 0, 0, 0, 0, 0 },     // U
    { 2, 0, 0, 1, 1, 0, 0, 2 },     // R
    { 1, 2, 0, 0, 2, 1, 0, 0 },     // F
    { 0, 0, 0, 0, 0, 0, 0, 0 },     // D
    { 0, 1, 2, 0, 0, 2, 1, 0 },     // L
    { 0, 0, 1, 2, 0, 0, 2, 1 },     // B
    { 1, 2, 1, 2, 2, 1, 2, 1 },     // ROT_URF3
    { 0, 0, 0, 0, 0, 0, 0, 0 },     // ROT_F2
    { 0, 0, 0, 0, 0, 0, 0, 0 },     // ROT_U4
    { 3, 3, 3, 3, 3, 3, 3, 3 }      // ROT_LR2
}};

const std::array< std::array< EDGES, 12 >, 10 > EdgeCubieMovePosition =
{{
    { UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR }, // U
    { FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR }, // R
    { UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR }, // F
    { UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR }, // D
    { UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR }, // L
    { UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB }, // B
    { UF, FR, DF, FL, UB, BR, DB, BL, UR, DR, DL, UL }, // ROT_URF3
    { DL, DF, DR, DB, UL, UF, UR, UB, FL, FR, BR, BL }, // ROT_F2
    { UB, UR, UF, UL, DB, DR, DF, DL, BR, FR, FL, BL }, // ROT_U4
    { UL, UF, UR, UB, DL, DF, DR, DB, FL, FR, BR, BL }  // ROT_LR2
}};

const std::array< std::array< unsigned int, 12 >, 10 >  EdgeCubieMoveOrientation =
{{
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // U
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // R
    { 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0 }, // F
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // D
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // L
    { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1 }, // B
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1 }, // ROT_URF3
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // ROT_F2
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 }, // ROT_U4
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}   // ROT_LR2
}};

unsigned int cornerOrientation(unsigned int a, unsigned int b)
{
    unsigned int ori(0);
    if (a < 3 && b < 3)  // two regular cubes
    {
        ori = a + b;
        if (ori >= 3)
            ori -= 3;
    }
    else if (a < 3 && 3 <= b) // cube b is in a mirrored state
    {
        ori = a + b;
        if (ori >= 6)
            ori -= 3; // the composition also is in a mirrored state
    }
    else if ( a >= 3 && 3 > b)  // cube a is in a mirrored state
    {
        ori = a - b;
        if (ori < 3)
            ori += 3;  // the composition is a mirrored cube
    }
    else if (a >= 3 && b >= 3) // if both cubes are in mirrored states
    {
        ori = a - b;
        if (ori < 0)
            ori += 3;  // the composition is a regular cube
    }
    return (ori);
}

void        Cube::rotation(const unsigned int& rot)
{
    corners     tmpCorners;
    tmpCorners.p = rotateCornPerm(m_corners.p, rot);
    tmpCorners.o = rotateCornOrient(m_corners.o, rot);
    m_corners = tmpCorners;

    edges       tmpEdges;
    tmpEdges.p = rotateEdgePerm(m_edges.p, rot);
    tmpEdges.o = rotateEdgeOrient(m_edges.o, rot);
    m_edges = tmpEdges;
}

std::array<CORNERS, 8>  Cube::rotateCornPerm(const std::array<CORNERS, 8>& cornPerm, const unsigned int& rot)
{
    std::array<CORNERS, 8>     tmp;
    for (unsigned int i = 0; i < 8; ++i)
    {
       tmp[i] = cornPerm[CornerCubieMovePosition[rot][i]];
    }
    return tmp;
}
std::array<unsigned int, 8>  Cube::rotateCornOrient(const std::array<unsigned int, 8>& cornOrient, const unsigned int& rot)
{
    std::array<unsigned int, 8>     tmp;
    for (unsigned int i = 0; i < 8; ++i)
    {
        //tmp[i] = (CornerCubieMoveOrientation[rot][i] + cornOrient[CornerCubieMovePosition[rot][i]]) % 3;
        tmp[i] = cornerOrientation(cornOrient[CornerCubieMovePosition[rot][i]], CornerCubieMoveOrientation[rot][i]);
    }
    return tmp;
}

edges                          Cube::rotateEdges(const edges& edgeCoord, const unsigned int& rot)
{
    edges tmp = edgeCoord;
    for (unsigned int i = 0; i < 12; ++i)
    {
        tmp.p[i] = edgeCoord.p[EdgeCubieMovePosition[rot][i]];
        tmp.o[i] = (EdgeCubieMoveOrientation[rot][i] + edgeCoord.o[EdgeCubieMovePosition[rot][i]]) % 2;
    }
    return tmp;
}

std::array<EDGES, 12>  Cube::rotateEdgePerm(const std::array<EDGES, 12>& edgePerm, const unsigned int& rot)
{
    std::array<EDGES, 12>     tmp;
    for (unsigned int i = 0; i < 12; ++i)
    {
       tmp[i] = edgePerm[EdgeCubieMovePosition[rot][i]];
    }
    return tmp;
}
std::array<unsigned int, 12>  Cube::rotateEdgeOrient(const std::array<unsigned int, 12>& edgeOrient, const unsigned int& rot)
{
    std::array<unsigned int, 12>     tmp;
    for (unsigned int i = 0; i < 12; ++i)
    {
        tmp[i] = (EdgeCubieMoveOrientation[rot][i] + edgeOrient[EdgeCubieMovePosition[rot][i]]) % 2;
    }
    return tmp;
}

void        Cube::up() { rotation(ROT_UP); }
void        Cube::upR() { rotation(ROT_UP); rotation(ROT_UP); rotation(ROT_UP); }
void        Cube::up2() { rotation(ROT_UP); rotation(ROT_UP); }

void        Cube::down() { rotation(ROT_DOWN); }
void        Cube::downR() { rotation(ROT_DOWN); rotation(ROT_DOWN); rotation(ROT_DOWN); }
void        Cube::down2() { rotation(ROT_DOWN); rotation(ROT_DOWN); }

void        Cube::right() { rotation(ROT_RIGHT); }
void        Cube::rightR() { rotation(ROT_RIGHT); rotation(ROT_RIGHT); rotation(ROT_RIGHT); }
void        Cube::right2() { rotation(ROT_RIGHT); rotation(ROT_RIGHT); }

void        Cube::left() { rotation(ROT_LEFT); }
void        Cube::leftR() { rotation(ROT_LEFT); rotation(ROT_LEFT); rotation(ROT_LEFT); }
void        Cube::left2() { rotation(ROT_LEFT); rotation(ROT_LEFT); }

void        Cube::front() { rotation(ROT_FRONT); }
void        Cube::frontR() { rotation(ROT_FRONT); rotation(ROT_FRONT); rotation(ROT_FRONT); }
void        Cube::front2() { rotation(ROT_FRONT); rotation(ROT_FRONT); }

void        Cube::back() { rotation(ROT_BACK); }
void        Cube::backR() { rotation(ROT_BACK); rotation(ROT_BACK); rotation(ROT_BACK); }
void        Cube::back2() { rotation(ROT_BACK); rotation(ROT_BACK); }

Cube        Cube::multCube(const Cube& first, const Cube& second)
{
    Cube tmp;

    tmp.m_corners = multCorners(first.m_corners, second.m_corners);
    tmp.m_edges   = multEdges(first.m_edges, second.m_edges);

    return (tmp);
}

corners         Cube::multCorners(const corners& first, const corners& second)
{
    corners tmp;
    for (unsigned int i = 0; i < 8; ++i)
    {
        tmp.p[i] = first.p[ second.p[i] ];
        tmp.o[i] = cornerOrientation(first.o[ second.p[i] ], second.o[i]);
    }
    return tmp;
}

std::array<CORNERS, 8>   Cube::multCornPerm(const std::array<CORNERS, 8>& first, const std::array<CORNERS, 8>& second)
{
    std::array<CORNERS, 8> tmp {};
    for (unsigned int i = 0; i < 8; ++i)
    {
        tmp[i] = first[ second[i] ];
    }
    return (tmp);
}

edges           Cube::multEdges(const edges& first, const edges& second)
{
    edges tmp;
    for (unsigned int i = 0; i < 12; ++i)
    {
        tmp.p[i] = first.p[ second.p[i]];
        tmp.o[i] = (second.o[i] + first.o[ second.p[i] ]) % 2;
    }
    return tmp;
}

std::array<EDGES, 12>     Cube::multEdgePerm(const std::array<EDGES, 12>& first, const std::array<EDGES, 12>& second)
{
    std::array<EDGES, 12> tmp {};
    for (unsigned int i = 0; i < 12; ++i)
    {
        tmp[i] = first[ second[i] ];
    }
    return (tmp);
}