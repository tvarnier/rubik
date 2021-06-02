#ifndef CUBIES3D_HPP
# define CUBIES3D_HPP

# include "VisualizerIncludes.hpp"

# define DEFAULT_FACE 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f
# define ORANGE_FACE 1.0f, 0.65f, 0.0f, 1.0f, 0.65f, 0.0f, 1.0f, 0.65f, 0.0f, 1.0f, 0.65f, 0.0f, 1.0f, 0.65f, 0.0f, 1.0f, 0.65f, 0.0f
# define RED_FACE 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
# define GREEN_FACE 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
# define BLUE_FACE 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
# define YELLOW_FACE 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f
# define WHITE_FACE 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f

# define SIZE_CUBIE 0.5f
# define DELTA_CUBIE 0.025f

class Cubies3d {
    public:
        Cubies3d()
        {
            m_position = glm::vec4(0.0f);
            m_rotation = glm::mat4(1.0f);
            m_isAnimated = false;
        }

        Cubies3d(const Cubies3d& cpy)
        {
            m_position = cpy.m_position;
            m_rotation = cpy.m_rotation;
            memcpy( m_colors, cpy.m_colors, sizeof(cpy.m_colors) );
            m_isAnimated = cpy.m_isAnimated;
        }

        void        setPosition(const glm::vec4& position) { m_position = position; }
        glm::vec4   getPosition() const { return (m_position); }

        void        setColor(const unsigned int& index, const float color[18]) { for ( int i = 0; i < 18; ++i ) m_colors[(index * 18) + i] = color[i]; }
        void        setColors(const float colors[108]) { memcpy( m_colors, colors, sizeof(float) * 108 ); }
        float*      getColors() const { return ((float*)m_colors); }

        void        setRotation(const glm::mat4& rotation) { m_rotation = rotation; }
        void        addRotation(const glm::mat4& rotation ) { m_rotation = rotation * m_rotation; }
        glm::mat4   getRotation() const { return (m_rotation); }

        void        animate() { m_isAnimated = true; }
        void        stopAnimation() { m_isAnimated = false; }
        bool        isAnimated() const { return (m_isAnimated); }

        Cubies3d&   operator=(Cubies3d const& cpy)
        {
            m_position = cpy.m_position;
            m_rotation = cpy.m_rotation;
            memcpy( m_colors, cpy.m_colors, sizeof(cpy.m_colors) );
            m_isAnimated =  cpy.m_isAnimated;
            return(*this);
        }

    private:
        glm::vec4   m_position;
        float       m_colors[108] = { DEFAULT_FACE, DEFAULT_FACE, DEFAULT_FACE, DEFAULT_FACE, DEFAULT_FACE, DEFAULT_FACE };
        glm::mat4   m_rotation;
        bool        m_isAnimated;
        
};

#endif