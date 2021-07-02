#include "Kociemba.hpp"

const std::map<std::string, Cube::moveFunction> Kociemba::P1MoveMap = {
    {"U", &Cube::up}, {"U'", &Cube::upR}, {"U2", &Cube::up2},
    {"D", &Cube::down}, {"D'", &Cube::downR}, {"D2", &Cube::down2},
    {"R", &Cube::right}, {"R'", &Cube::rightR}, {"R2", &Cube::right2},
    {"L", &Cube::left}, {"L'", &Cube::leftR}, {"L2", &Cube::left2},
    {"F", &Cube::front}, {"F'", &Cube::frontR}, {"F2", &Cube::front2},
    {"B", &Cube::back}, {"B'", &Cube::backR}, {"B2", &Cube::back2}
};

const std::map<std::string, Cube::moveFunction> Kociemba::P2MoveMap = {
    {"U",  &Cube::up}, {"U'", &Cube::upR}, {"U2", &Cube::up2},
    {"D",  &Cube::down}, {"D'", &Cube::downR}, {"D2", &Cube::down2},
    {"R2", &Cube::right2},
    {"L2", &Cube::left2},
    {"F2", &Cube::front2},
    {"B2", &Cube::back2}
};