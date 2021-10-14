#ifndef RUBIK3D_H
# define RUBIK3D_H

# include "VisualizerIncludes.hpp"

# include "../Cubies3d/Cubies3d.hpp"

struct Rotation
{
    bool        isAnimated  = false;
    bool        isRotating  = false;
    glm::vec3   axis        = glm::vec3( 0.0f, 0.0f, 0.0f );
    glm::vec4   center      = glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f );
    float       angle       = 0.0f;
    float       speed       = 0.0f;
    float       reverse     = 1.0f;
    std::string move;
    float       limit       = -90.0f;
};

class Rubik3d {
    public:
        Rotation        rot;

        Rubik3d();

        Cubies3d        getCubie( const unsigned int& index );

        void            rotate(const std::string move);
        void            endRotation();

        glm::mat4       getRotation() const;

    private:
        Cubies3d        m_rubik[ 3 ][ 3 ][ 3 ];
        glm::mat4       m_rotation;

        std::array<Cubies3d, 2>     getCubies(const unsigned int op[2]);
        std::array<Cubies3d, 2>     swapCubie(const unsigned int op[2], std::array<Cubies3d, 2> replacer);
        void                        invert(const unsigned int op1[2], const unsigned int op2[2], const unsigned int op3[2], const unsigned int op4[2]);
        
        void                        front(bool reverse);
        void                        back(bool reverse);
        void                        right(bool reverse);
        void                        left(bool reverse);
        void                        up(bool reverse);
        void                        down(bool reverse);
};

#endif