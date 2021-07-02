#include "Cube.hpp"

std::map<std::string, Cube::moveFunction> Cube::moveMap = {
    {"U", &Cube::up}, {"U'", &Cube::upR}, {"U2", &Cube::up2},
    {"D", &Cube::down}, {"D'", &Cube::downR}, {"D2", &Cube::down2},
    {"R", &Cube::right}, {"R'", &Cube::rightR}, {"R2", &Cube::right2},
    {"L", &Cube::left}, {"L'", &Cube::leftR}, {"L2", &Cube::left2},
    {"F", &Cube::front}, {"F'", &Cube::frontR}, {"F2", &Cube::front2},
    {"B", &Cube::back}, {"B'", &Cube::backR}, {"B2", &Cube::back2}
};

Cube::Cube()
{
    /*for (CORNERS i = URF; i <  8; i = (CORNERS) ((unsigned int)i + 1) )
        m_corners[i] = std::make_pair(i, 0);

    for (  EDGES i = UR;  i < 12; i =   (EDGES) ((unsigned int)i + 1) )
        m_edges[i] = std::make_pair(i, 0);*/
}

int         Cube::move(const std::string m) { if (moveMap[m]) { (this->*moveMap[m])() ; return (0); } else return (1); }

void        Cube::shuffle(int iterations)
{
    int     lastMove(-1);
    /*moveFunction    arrayMoves[6][3] = {
        { &Cube::up, &Cube::upR, &Cube::up2 },
        { &Cube::down, &Cube::downR, &Cube::down2 },
        { &Cube::right, &Cube::rightR, &Cube::right2 },
        { &Cube::left, &Cube::leftR, &Cube::left2 },
        { &Cube::front, &Cube::frontR, &Cube::front2 },
        { &Cube::back, &Cube::backR, &Cube::back2 }
    };*/
    moveFunction    arrayMoves[6][3] = {
        { &Cube::up, &Cube::upR, &Cube::up2 },
        { &Cube::down, &Cube::downR, &Cube::down2 },
        { &Cube::right2, &Cube::right2, &Cube::right2 },
        { &Cube::left2, &Cube::left2, &Cube::left2 },
        { &Cube::front2, &Cube::front2, &Cube::front2 },
        { &Cube::back2, &Cube::back2, &Cube::back2 }
    };

    srand (time(NULL));

    int r = rand() % 18 + 0;

    while (iterations)
    {
        if (r / 3 == lastMove)
            r += 3;
        for (auto it = moveMap.begin(); it != moveMap.end(); ++it)
            if (it->second == arrayMoves[r / 3][r % 3])      
                std::printf("%s \n", std::string(it->first).c_str());
        (this->*arrayMoves[r / 3][r % 3])();
        lastMove = r / 3;
        r = rand() % 15 + 0;
        --iterations;
    }
}

Cube&               Cube::operator = (const Cube& other)
{
    // Guard self assignment
    if (this == &other)
        return *this;

    m_corners = other.m_corners; 
    m_edges = other.m_edges; 
    return *this;
}