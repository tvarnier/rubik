#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "VisualizerIncludes.hpp"

# include "./Rubik3d/Rubik3d.hpp"
# include "./Shader/Shader.hpp"
# include "./Camera/Camera.hpp"

class Visualizer {
    public:
        Visualizer(const unsigned int& width, const unsigned int& height);
        ~Visualizer();

        int             draw();

        GLFWwindow*     window;

        unsigned int    m_width;
        unsigned int    m_height;
        Camera          camera;
        float           lastX;
        float           lastY;
        bool            firstMouse;

        float           angle;

        float           deltaTime;
        float           lastFrame;

    private:

        Shader          ourShader;

        unsigned int    VBO, VAO, color_buffer;

        Rubik3d         rubik3d;

        int             init();

        glm::vec4   rotateAround( const glm::vec4&   aPointToRotate, const glm::vec4&   aRotationCenter, const glm::mat4x4& aRotationMatrix );
        
        void processInput(GLFWwindow *window);
};

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void error_callback(int error, const char* description);

#endif