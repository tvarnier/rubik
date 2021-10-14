#include "Rubik3d.hpp"

Rubik3d::Rubik3d()
{
    m_rotation = glm::mat4(1.0f);

    float orange_face_array[18] = {ORANGE_FACE};
    float red_face_array[18] = {RED_FACE};
    float green_face_array[18] = {GREEN_FACE};
    float blue_face_array[18] = {BLUE_FACE};
    float yellow_face_array[18] = {YELLOW_FACE};
    float white_face_array[18] = {WHITE_FACE};

    for (int slice = 0; slice < 3; ++slice)
        for (int row = 0; row < 3; ++row)
            for (int column = 0; column < 3; ++column)
            {
                if (column == 0) m_rubik[slice][row][column].setColor(0, orange_face_array);
                if (column == 2) m_rubik[slice][row][column].setColor(1, red_face_array);
                if (row == 0) m_rubik[slice][row][column].setColor(2, green_face_array);
                if (row == 2) m_rubik[slice][row][column].setColor(3, blue_face_array);
                if (slice == 0) m_rubik[slice][row][column].setColor(4, yellow_face_array);
                if (slice == 2) m_rubik[slice][row][column].setColor(5, white_face_array);
                m_rubik[slice][row][column].setPosition( glm::vec4( ((row - 1) * (SIZE_CUBIE + DELTA_CUBIE)),
                                                                    ((slice - 1) * (SIZE_CUBIE + DELTA_CUBIE)),
                                                                    ((column - 1) * (SIZE_CUBIE + DELTA_CUBIE)),
                                                                    1.0f) );
            }
}

Cubies3d    Rubik3d::getCubie(const unsigned int& index) { return (m_rubik[index / 9][ (index % 9) / 3][ index % 3 ]); }

glm::mat4   Rubik3d::getRotation() const { return (m_rotation); }

struct      faceToMove { int sliceMin = 0; int sliceMax = 2; int rowMin = 0; int rowMax = 2; int colMin = 0; int colMax = 2; };

void        Rubik3d::rotate(const std::string move)
{
    faceToMove  f;

    rot.move       = move;
    rot.isAnimated = true;
    rot.isRotating = false;
    rot.axis       = glm::vec3(0.0f, 0.0f, 0.0f);
    rot.angle      = 0.0f;
    rot.speed      = -360.0f;
    rot.reverse    = 1.0f;
    rot.limit      = -90.0f;

    if (move.at(0) == 'F') { f.colMin = f.colMax; rot.axis = glm::vec3(0.0f, 0.0f, 1.0f); }
    if (move.at(0) == 'B') { f.colMax = f.colMin; rot.axis = glm::vec3(0.0f, 0.0f, -1.0f); }
    if (move.at(0) == 'R') { f.rowMin = f.rowMax; rot.axis = glm::vec3(1.0f, 0.0f, 0.0f); }
    if (move.at(0) == 'L') { f.rowMax = f.rowMin; rot.axis = glm::vec3(-1.0f, 0.0f, 0.0f); }
    if (move.at(0) == 'U') { f.sliceMin = f.sliceMax; rot.axis = glm::vec3(0.0f, 1.0f, 0.0f); }
    if (move.at(0) == 'D') { f.sliceMax = f.sliceMin; rot.axis = glm::vec3(0.0f, -1.0f, 0.0f); }

    if (move.at(0) == 'X') { rot.isRotating = true; rot.axis = glm::vec3(1.0f, 0.0f, 0.0f); }
    if (move.at(0) == 'Y') { rot.isRotating = true; rot.axis = glm::vec3(0.0f, 1.0f, 0.0f); }
    if (move.at(0) == 'Z') { rot.isRotating = true; rot.axis = glm::vec3(0.0f, 0.0f, -1.0f); }

    if (move.length() == 2)
    {
        if (move.at(1) == '\'')
        {
            rot.reverse = -1.0f;
            rot.speed   = rot.speed * rot.reverse;
        }
        if (move.at(1) == '2')
            rot.limit = -180.0f;
    }

    if (!rot.isRotating)
        for (int slice = f.sliceMin; slice <= f.sliceMax; ++slice)
            for (int row = f.rowMin; row <= f.rowMax; ++row)
                for (int column = f.colMin; column <= f.colMax; ++column)
                    m_rubik[slice][row][column].animate();
}

void        Rubik3d::endRotation()
{
    if (rot.isAnimated && ((rot.reverse == 1.0f && rot.angle <= rot.limit) || (rot.reverse == -1.0f && rot.angle >= rot.limit * rot.reverse)))
    {
        rot.angle = rot.limit * rot.reverse;
        if (!rot.isRotating)
        {
            for (int slice = 0; slice < 3; ++slice)
                for (int row = 0; row < 3; ++row)
                    for (int column = 0; column < 3; ++column)
                        if (m_rubik[slice][row][column].isAnimated())
                        {
                            m_rubik[slice][row][column].stopAnimation();
                            m_rubik[slice][row][column].addRotation( glm::rotate(glm::radians(rot.angle), rot.axis));
                        }
            bool reverse = (rot.move.length() == 2 && rot.move.at(1) == '\'');
            unsigned int number_move = (rot.move.length() == 2 && rot.move.at(1) == '2') ? 2 : 1;
            while (number_move--)
            {
                if (rot.move.at(0) == 'F')
                    front(reverse);
                if (rot.move.at(0) == 'B')
                    back(reverse);
                if (rot.move.at(0) == 'R')
                    right(reverse);
                if (rot.move.at(0) == 'L')
                    left(reverse);
                if (rot.move.at(0) == 'U')
                    up(reverse);
                if (rot.move.at(0) == 'D')
                    down(reverse);
            }
        }
        else
            m_rotation = glm::rotate(glm::radians(rot.angle), rot.axis) * m_rotation;
        rot.isAnimated = false;
        rot.isRotating = false;
        rot.axis       = glm::vec3(0.0f, 0.0f, 0.0f);
        rot.angle      = 0.0f;
        rot.speed      = 0.0f;
        rot.reverse    = 1.0f;
        rot.limit      = -90.0f;
    }
}