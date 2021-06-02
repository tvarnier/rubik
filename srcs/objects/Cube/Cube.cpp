# include "Cube.hpp"

// ----- Constructors ----- //

Cube::Cube() : m_cube({0x00000000, 0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555 }), m_center({0, 1, 2, 3, 4, 5})
{
    initMoveMap();
}
Cube::Cube(const Cube& other)
{
    m_cube = other.m_cube;
}

void        Cube::print()
{
    lib::printendl("===========================\n");

    int face = 0;
    int row = 0;

    for (row = 0; row < 3; ++row)
    {
        lib::print("        ");
        for (int i = 0; i < 3; ++i)
        {
            getColor((COLOR)getColorFromIndex(face, row, i));
            lib::print(" ");
        }
        cout << std::endl;
    }

    lib::printendl("");

    for (row = 0; row < 3; ++row)
    {
        for (face = 1; face < 5; ++face)
        {
            for (int i = 0; i < 3; ++i)
            {
                getColor((COLOR)getColorFromIndex(face, row, i));
                lib::print(" ");
            }
            lib::print("  ");
        }
        cout << std::endl;
    }

    lib::printendl("");

    for (row = 0; row < 3; ++row)
    {
        lib::print("        ");
        for (int i = 0; i < 3; ++i)
        {
            getColor((COLOR)getColorFromIndex(face, row, i));
            lib::print(" ");
        }
        cout << std::endl;
    }

    lib::printendl("\n===========================");
}

void        Cube::initMoveMap()
{
    std::array<std::pair<std::string, moveFunction>, 18> moves = {{
        {"U", &Cube::up}, {"U'", &Cube::upR}, {"U2", &Cube::up2},
        {"D", &Cube::down}, {"D'", &Cube::downR}, {"D2", &Cube::down2},
        {"R", &Cube::right}, {"R'", &Cube::rightR}, {"R2", &Cube::right2},
        {"L", &Cube::left}, {"L'", &Cube::leftR}, {"L2", &Cube::left2},
        {"F", &Cube::front}, {"F'", &Cube::frontR}, {"F2", &Cube::front2},
        {"B", &Cube::back}, {"B'", &Cube::backR}, {"B2", &Cube::back2}
    }};

    for ( int i = 0; i < 18; ++i)
        moveMap.insert(moves[i]);
}

int         Cube::move(const std::string m) { if (moveMap[m]) { (this->*moveMap[m])() ; return (0); } else return (1); }

void        Cube::getColor(const COLOR color)
{
    switch ( color )
        {
            case COLOR::CWHITE:
                lib::print(WHITE, "W");
                break;
            case COLOR::CGREEN:
                lib::print(GREEN, "G");
                break;
            case COLOR::CRED:
                lib::print(RED, "R");
                break;
            case COLOR::CBLUE:
                lib::print(BLUE, "B");
                break;
            case COLOR::CORANGE:
                lib::print(MAGENTA, "O");
                break;
            case COLOR::CYELLOW:
                lib::print(YELLOW, "Y");
                break;
            default:
                break;
        }
}

int         Cube::getColorFromIndex(int face, int x, int y)
{
    int     face_value = m_cube[face];
    int     index = x * 3 + y;
    int     pos[] = { 0, 1, 2, 7, -1, 3, 6, 5, 4  };

    index = pos[index];
    if (index == -1)
        return (m_center[face]);
    return ( face_value >> (( 8 - index - 1) * 4) & 0xF );
}

int         Cube::getColorFromPos(int face, int pos)
{
    int     face_value = m_cube[face];
    return ( face_value >> (( 8 - pos - 1) * 4) & 0xF );
}