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
    { UFL, URF, UBR, ULB, DLF, DFR, DRB, DBL }      // MIRR_LR2
    
}};
const std::array< std::array< unsigned int,  8 >, 10 >  CornerCubieMoveOrientation =
{{
    { 0, 0, 0, 0, 0, 0, 0, 0 },     //U
    { 2, 0, 0, 1, 1, 0, 0, 2 },     //R
    { 1, 2, 0, 0, 2, 1, 0, 0 },     //F
    { 0, 0, 0, 0, 0, 0, 0, 0 },     //D
    { 0, 1, 2, 0, 0, 2, 1, 0 },     //L
    { 0, 0, 1, 2, 0, 0, 2, 1 },     //B
    { 1, 2, 1, 2, 2, 1, 2, 1 },     // ROT_URF3
    { 0, 0, 0, 0, 0, 0, 0, 0 },     // ROT_F2
    { 0, 0, 0, 0, 0, 0, 0, 0 },     // ROT_U4
    { 3, 3, 3, 3, 3, 3, 3, 3 }      // MIRR_LR2
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
    { UL, UF, UR, UB, DL, DF, DR, DB, FL, FR, BR, BL }  // MIRR_LR2
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
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }  // MIRR_LR2
}};

void        Cube::rotation(const unsigned int& rot)
{
    corners     tmpCorners;
    for (unsigned int i = 0; i < 8; ++i)
    {
        tmpCorners.p[i] = m_corners.p[CornerCubieMovePosition[rot][i]];
        tmpCorners.o[i] = (CornerCubieMoveOrientation[rot][i] + m_corners.o[CornerCubieMovePosition[rot][i]]) % 3;
    }
    m_corners = tmpCorners;

    edges       tmpEdges;
    for (unsigned int i = 0; i < 12; ++i)
    {
        tmpEdges.p[i] = m_edges.p[EdgeCubieMovePosition[rot][i]];
        tmpEdges.o[i] = (EdgeCubieMoveOrientation[rot][i] + m_edges.o[EdgeCubieMovePosition[rot][i]]) % 2;
    }
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
std::array<EDGES, 12>  Cube::rotateEdgePerm(const std::array<EDGES, 12>& edgePerm, const unsigned int& rot)
{
    std::array<EDGES, 12>     tmp;
    for (unsigned int i = 0; i < 12; ++i)
    {
       tmp[i] = edgePerm[EdgeCubieMovePosition[rot][i]];
    }
    return tmp;
}

void        Cube::up() { rotation(UP); }
void        Cube::upR() { rotation(UP); rotation(UP); rotation(UP); }
void        Cube::up2() { rotation(UP); rotation(UP); }

void        Cube::down() { rotation(DOWN); }
void        Cube::downR() { rotation(DOWN); rotation(DOWN); rotation(DOWN); }
void        Cube::down2() { rotation(DOWN); rotation(DOWN); }

void        Cube::right() { rotation(RIGHT); }
void        Cube::rightR() { rotation(RIGHT); rotation(RIGHT); rotation(RIGHT); }
void        Cube::right2() { rotation(RIGHT); rotation(RIGHT); }

void        Cube::left() { rotation(LEFT); }
void        Cube::leftR() { rotation(LEFT); rotation(LEFT); rotation(LEFT); }
void        Cube::left2() { rotation(LEFT); rotation(LEFT); }

void        Cube::front() { rotation(FRONT); }
void        Cube::frontR() { rotation(FRONT); rotation(FRONT); rotation(FRONT); }
void        Cube::front2() { rotation(FRONT); rotation(FRONT); }

void        Cube::back() { rotation(BACK); }
void        Cube::backR() { rotation(BACK); rotation(BACK); rotation(BACK); }
void        Cube::back2() { rotation(BACK); rotation(BACK); }


Cube        Cube::operator + (Cube const &obj) {
    Cube    res;

    for (unsigned int i = 0; i < 8; ++i)
    {
        res.m_corners.p[i] = m_corners.p[ obj.m_corners.p[i] ],
        res.m_corners.o[i] = (obj.m_corners.o[i] + m_corners.o[obj.m_corners.p[i]]) % 3;
    }

    for (unsigned int i = 0; i < 12; ++i)
    {
        res.m_edges.p[i] = m_edges.p[ obj.m_edges.p[i] ],
        res.m_edges.o[i] = (obj.m_edges.o[i] + m_edges.o[obj.m_edges.p[i]]) % 2;
    }
    
    return (res);
}

std::array<CORNERS, 8>  Cube::multCornPerm(const std::array<CORNERS, 8>& first, const std::array<CORNERS, 8>& second)
{
    std::array<CORNERS, 8>  res;
    for (unsigned int i = 0; i < 8; ++i)
        res[i] = first[ second[i] ];
    return res;
}

std::array<EDGES, 12>    Cube::multEdgePerm(const std::array<EDGES, 12>& first, const std::array<EDGES, 12>& second)
{
    std::array<EDGES, 12>  res;
    for (unsigned int i = 0; i < 12; ++i)
        res[i] = first[ second[i] ];
    return res;
}