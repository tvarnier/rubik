#include "Rubik3d.hpp"

# define COORD( slice, row, col ) (slice * 9 + row * 3 + col * 1) 

std::array<Cubies3d, 2>         Rubik3d::getCubies(const unsigned int op[2])
{
    std::array<Cubies3d, 2> replacer;
    
    replacer[0] = getCubie(op[0]);
    replacer[1] = getCubie(op[1]);

    return replacer;
}

std::array<Cubies3d, 2>         Rubik3d::swapCubie(const unsigned int op[2], std::array<Cubies3d, 2> replacer)
{    
    std::array<Cubies3d, 2> tmp = getCubies(op);

    m_rubik[op[0] / 9][ (op[0] % 9) / 3][ op[0] % 3 ].setColors(replacer[0].getColors());
    m_rubik[op[0] / 9][ (op[0] % 9) / 3][ op[0] % 3 ].setRotation(replacer[0].getRotation());
    m_rubik[op[1] / 9][ (op[1] % 9) / 3][ op[1] % 3 ].setColors(replacer[1].getColors());
    m_rubik[op[1] / 9][ (op[1] % 9) / 3][ op[1] % 3 ].setRotation(replacer[1].getRotation());

    return tmp;
}

void        Rubik3d::invert(const unsigned int op1[2], const unsigned int op2[2], const unsigned int op3[2], const unsigned int op4[2])
{
    std::array<Cubies3d, 2>   replacer;

    replacer = getCubies(op1);

    replacer = swapCubie(op2, replacer);
    replacer = swapCubie(op3, replacer);
    replacer = swapCubie(op4, replacer);
    replacer = swapCubie(op1, replacer);
}

void        Rubik3d::front(bool reverse)
{
    unsigned int inv1[2] = {
        COORD(2, 0, 2),
        COORD(1, 0, 2)
    };
    unsigned int inv2[2] = {
        COORD(0, 0, 2),
        COORD(0, 1, 2)
    };
    unsigned int inv3[2] = {
        COORD(0, 2, 2),
        COORD(1, 2, 2)
    };
    unsigned int inv4[2] = {
        COORD(2, 2, 2),
        COORD(2, 1, 2)
    };
    if (reverse)
        invert(inv1, inv2, inv3, inv4);
    else
        invert(inv4, inv3, inv2, inv1);
}

void        Rubik3d::back(bool reverse)
{
    unsigned int inv1[2] = {
        COORD(2, 2, 0),
        COORD(1, 2, 0)
    };
    unsigned int inv2[2] = {
        COORD(0, 2, 0),
        COORD(0, 1, 0)
    };
    unsigned int inv3[2] = {
        COORD(0, 0, 0),
        COORD(1, 0, 0)
    };
    unsigned int inv4[2] = {
        COORD(2, 0, 0),
        COORD(2, 1, 0)
    };
    if (reverse)
        invert(inv1, inv2, inv3, inv4);
    else
        invert(inv4, inv3, inv2, inv1);
}

void        Rubik3d::right(bool reverse)
{
    unsigned int inv1[2] = {
        COORD(2, 2, 2),
        COORD(1, 2, 2)
    };
    unsigned int inv2[2] = {
        COORD(0, 2, 2),
        COORD(0, 2, 1)
    };
    unsigned int inv3[2] = {
        COORD(0, 2, 0),
        COORD(1, 2, 0)
    };
    unsigned int inv4[2] = {
        COORD(2, 2, 0),
        COORD(2, 2, 1)
    };
    if (reverse)
        invert(inv1, inv2, inv3, inv4);
    else
        invert(inv4, inv3, inv2, inv1);
}

void        Rubik3d::left(bool reverse)
{
    unsigned int inv1[2] = {
        COORD(2, 0, 0),
        COORD(1, 0, 0)
    };
    unsigned int inv2[2] = {
        COORD(0, 0, 0),
        COORD(0, 0, 1)
    };
    unsigned int inv3[2] = {
        COORD(0, 0, 2),
        COORD(1, 0, 2)
    };
    unsigned int inv4[2] = {
        COORD(2, 0, 2),
        COORD(2, 0, 1)
    };
    if (reverse)
        invert(inv1, inv2, inv3, inv4);
    else
        invert(inv4, inv3, inv2, inv1);
}

void        Rubik3d::up(bool reverse)
{
    unsigned int inv1[2] = {
        COORD(2, 0, 0),
        COORD(2, 0, 1)
    };
    unsigned int inv2[2] = {
        COORD(2, 0, 2),
        COORD(2, 1, 2)
    };
    unsigned int inv3[2] = {
        COORD(2, 2, 2),
        COORD(2, 2, 1)
    };
    unsigned int inv4[2] = {
        COORD(2, 2, 0),
        COORD(2, 1, 0)
    };
    if (reverse)
        invert(inv1, inv2, inv3, inv4);
    else
        invert(inv4, inv3, inv2, inv1);
}

void        Rubik3d::down(bool reverse)
{
    unsigned int inv1[2] = {
        COORD(0, 0, 0),
        COORD(0, 1, 0)
    };
    unsigned int inv2[2] = {
        COORD(0, 2, 0),
        COORD(0, 2, 1)
    };
    unsigned int inv3[2] = {
        COORD(0, 2, 2),
        COORD(0, 1, 2)
    };
    unsigned int inv4[2] = {
        COORD(0, 0, 2),
        COORD(0, 0, 1)
    };
    if (reverse)
        invert(inv1, inv2, inv3, inv4);
    else
        invert(inv4, inv3, inv2, inv1);
}