#include "Cube.hpp"

std::map<std::string, Cube::moveFunction> Cube::moveMap = {
    {"U", &Cube::up}, {"U'", &Cube::upR}, {"U2", &Cube::up2},
    {"D", &Cube::down}, {"D'", &Cube::downR}, {"D2", &Cube::down2},
    {"R", &Cube::right}, {"R'", &Cube::rightR}, {"R2", &Cube::right2},
    {"L", &Cube::left}, {"L'", &Cube::leftR}, {"L2", &Cube::left2},
    {"F", &Cube::front}, {"F'", &Cube::frontR}, {"F2", &Cube::front2},
    {"B", &Cube::back}, {"B'", &Cube::backR}, {"B2", &Cube::back2}
};

Cube::Cube() {}

int         Cube::move(const std::string m) { if (moveMap[m]) { (this->*moveMap[m])() ; return (0); } else return (1); }
bool        Cube::isMove(const std::string m) { return (moveMap[m]); }

std::vector<std::string>    Cube::shuffle(int iterations)
{
    std::vector<std::string> shuffleMoves = {};
    int     lastMove(-1);
    std::string     arrayMoves[6][3] = {
        { "U", "U2", "U'"},
        { "D", "D2", "D'"},
        { "R", "R2", "R'"},
        { "L", "L2", "L'"},
        { "F", "F2", "F'"},
        { "B", "B2", "B'"}
    };
    srand (time(NULL));

    while (iterations)
    {
        int r = rand() % 18 + 0;
        if (r / 3 == lastMove)
            r = (r + 3) % 18;
        shuffleMoves.emplace_back(arrayMoves[r / 3][r % 3]);
        move(arrayMoves[r / 3][r % 3]);
        lastMove = r / 3;
        --iterations;
    }

    return (shuffleMoves);
}

Cube&               Cube::operator = (const Cube& other)
{
    if (this == &other)
        return *this;
    m_corners = other.m_corners; 
    m_edges = other.m_edges; 
    return *this;
}