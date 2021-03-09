# include "Cube.hpp"


/* ========================================================= */
/* =======-------          FUNCTIONS          -------======= */
/* ========================================================= */

int         changeByte(int value, int pos, int newValue)
{
    return (value & ~(0xF << ((8 - pos - 1) * 4))) | (newValue << ((8 - pos - 1) * 4));
}

int         reverseRotate(int x)
{
    return (x<<8) | (x>>(32-8));
}

int         rotate(int x)
{
    return (x>>8) | (x<<(32-8));
}

std::array<int, 3>         Cube::getValuesCubie(int op[4])
{
    int face = op[0];
    std::array<int, 3> replacer;
    
    replacer[0] = getColorFromPos(face, op[1]);
    replacer[1] = getColorFromPos(face, op[2]);
    replacer[2] = getColorFromPos(face, op[3]);

    return replacer;
}

std::array<int, 3>         Cube::swapCubie(int op[4], std::array<int, 3> replacer)
{
    int face = op[0];
    
    std::array<int, 3> tmp = getValuesCubie(op);
    m_cube[face] = changeByte(m_cube[face], op[1], replacer[0]);
    m_cube[face] = changeByte(m_cube[face], op[2], replacer[1]);
    m_cube[face] = changeByte(m_cube[face], op[3], replacer[2]);

    return tmp;
}

void        Cube::invert(int op1[4], int op2[4], int op3[4], int op4[4])
{
    std::array<int, 3>   replacer;

    replacer = getValuesCubie(op1);

    replacer = swapCubie(op2, replacer);
    replacer = swapCubie(op3, replacer);
    replacer = swapCubie(op4, replacer);
    replacer = swapCubie(op1, replacer);
}

/* ========================================================= */
/* =======-------          ---------          -------======= */
/* ========================================================= */


void        Cube::up()
{
    m_cube[UP] = rotate(m_cube[UP]);
    int inv1[4] = {FRONT, UR, U, UL};
    int inv2[4] = {LEFT, UR, U, UL};
    int inv3[4] = {BACK, UR, U, UL};
    int inv4[4] = {RIGHT, UR, U, UL};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::upR()
{
    m_cube[UP] = reverseRotate(m_cube[UP]);
    int inv1[4] = {FRONT, UR, U, UL};
    int inv2[4] = {RIGHT, UR, U, UL};
    int inv3[4] = {BACK, UR, U, UL};
    int inv4[4] = {LEFT, UR, U, UL};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::up2() { up(); up(); }


/* ---------------------------------------------- */

void        Cube::down()
{
    m_cube[DOWN] = rotate(m_cube[DOWN]);
    int inv1[4] = {FRONT, DR, D, DL};
    int inv2[4] = {RIGHT, DR, D, DL};
    int inv3[4] = {BACK, DR, D, DL};
    int inv4[4] = {LEFT, DR, D, DL};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::downR()
{
    m_cube[DOWN] = reverseRotate(m_cube[DOWN]);
    int inv1[4] = {FRONT, DR, D, DL};
    int inv2[4] = {LEFT, DR, D, DL};
    int inv3[4] = {BACK, DR, D, DL};
    int inv4[4] = {RIGHT, DR, D, DL};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::down2() { down(); down(); }

/* ---------------------------------------------- */

void        Cube::right()
{
    m_cube[RIGHT] = rotate(m_cube[RIGHT]);
    int inv1[4] = {BACK, UL, L, DL};
    int inv2[4] = {DOWN, UR, U, UL};
    int inv3[4] = {FRONT, DR, R, UR};
    int inv4[4] = {UP, DL, D, DR};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::rightR()
{
    m_cube[RIGHT] = reverseRotate(m_cube[RIGHT]);
    int inv1[4] = {BACK, UL, L, DL};
    int inv2[4] = {UP, DL, D, DR};
    int inv3[4] = {FRONT, DR, R, UR};
    int inv4[4] = {DOWN, UR, U, UL};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::right2() { right(); right(); }

/* ---------------------------------------------- */

void        Cube::left()
{
    m_cube[LEFT] = rotate(m_cube[LEFT]);
    int inv1[4] = {FRONT, UL, L, DL};
    int inv2[4] = {DOWN, UR, U, UL};
    int inv3[4] = {BACK, DR, R, UR};
    int inv4[4] = {UP, DL, D, DR};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::leftR()
{
    m_cube[LEFT] = reverseRotate(m_cube[LEFT]);
    int inv1[4] = {FRONT, UL, L, DL};
    int inv2[4] = {UP, DL, D, DR};
    int inv3[4] = {BACK, DR, R, UR};
    int inv4[4] = {DOWN, UR, U, UL};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::left2() { left(); left(); }

/* ---------------------------------------------- */

void        Cube::front()
{
    m_cube[FRONT] = rotate(m_cube[FRONT]);
    int inv1[4] = {RIGHT, UL, L, DL};
    int inv2[4] = {DOWN, UR, U, UL};
    int inv3[4] = {LEFT, DR, R, UR};
    int inv4[4] = {UP, DL, D, DR};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::frontR()
{
    m_cube[FRONT] = reverseRotate(m_cube[FRONT]);
    int inv1[4] = {RIGHT, UL, L, DL};
    int inv2[4] = {UP, DL, D, DR};
    int inv3[4] = {LEFT, DR, R, UR};
    int inv4[4] = {DOWN, UR, U, UL};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::front2() { front(); front(); }

/* ---------------------------------------------- */

void        Cube::back()
{
    m_cube[BACK] = rotate(m_cube[BACK]);
    int inv1[4] = {LEFT, UL, L, DL};
    int inv2[4] = {DOWN, UR, U, UL};
    int inv3[4] = {RIGHT, DR, R, UR};
    int inv4[4] = {UP, DL, D, DR};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::backR()
{
    m_cube[BACK] = reverseRotate(m_cube[BACK]);
    int inv1[4] = {LEFT, UL, L, DL};
    int inv2[4] = {UP, DL, D, DR};
    int inv3[4] = {RIGHT, DR, R, UR};
    int inv4[4] = {DOWN, UR, U, UL};
    invert(inv1, inv2, inv3, inv4);
}

void        Cube::back2() { back(); back(); }