#include "Visualizer.hpp"

Visualizer::Visualizer(const unsigned int& widht, const unsigned int& height) : ourShader()
{
    m_width = widht;
    m_height = height;
    init();
}

Visualizer::~Visualizer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &color_buffer);

    glfwDestroyWindow(window);

    glfwTerminate();
}

int     Visualizer::init()
{
    camera = Camera(glm::vec3(2.5f, 1.5f, 2.5f));
    lastX = m_width / 2.0f;
    lastY = m_height / 2.0f;
    firstMouse = true;

    angle = 20.0f * (float)glfwGetTime();

    deltaTime = 0.0f;
    lastFrame = 0.0f;

    lastRotation = 0.0f;

    #ifdef __APPLE__
        glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
    #endif

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    #endif

    window = glfwCreateWindow(m_width, m_height, "Rubik", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)&(framebuffer_size_callback));
    glfwSetErrorCallback((GLFWerrorfun)&error_callback);
    glfwSetWindowCloseCallback(window, window_close_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    ourShader = Shader("./resources/shaders/3.3.shader.vs", "./resources/shaders/3.3.shader.fs");

    float vertices[] = {
        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,

        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,

        -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,

         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,

        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,

        -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
         SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f,
        -SIZE_CUBIE / 2.0f,  SIZE_CUBIE / 2.0f, -SIZE_CUBIE / 2.0f
    };

    float colors[] = { DEFAULT_FACE, DEFAULT_FACE, DEFAULT_FACE, DEFAULT_FACE, DEFAULT_FACE, DEFAULT_FACE };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &color_buffer);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), 0, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), ((void*)0));
    glEnableVertexAttribArray(1);

    ourShader.use();

    return (0);
}

int     Visualizer::draw()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    ourShader.use();

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    rubik3d.endRotation();

    glm::mat4 rubikRotation = rubik3d.getRotation();
    glm::mat4 view;
    glm::vec4 cameraPosition = glm::vec4(camera.GetPosition(), 1.0f);

    if (rubik3d.rot.isRotating)
    {
        float angleRad = glm::radians(rubik3d.rot.angle);
        glm::mat4x4 cameraMatRot = glm::rotate( angleRad, rubik3d.rot.axis );
        rubikRotation = glm::rotate(angleRad, rubik3d.rot.axis) * rubikRotation ;
    }
    view = glm::lookAt(glm::vec3(cameraPosition), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    view = view * rubikRotation;
    ourShader.setMat4("view", view);

    if (rubik3d.rot.isAnimated)
    {
	rubik3d.rot.angle += ((rubik3d.rot.speed) * deltaTime);
        lastRotation = currentFrame;
    }

    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 27; i++)
    {
        Cubies3d cubie3d = rubik3d.getCubie(i);
        float* color = cubie3d.getColors();
        glm::vec4 position = cubie3d.getPosition();
        glm::mat4 cubieRotation = cubie3d.getRotation();
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 108 * sizeof(float), color);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), ((void*)0));
        glEnableVertexAttribArray(1);

        glm::mat4 model = glm::mat4(1.0f);

        if (cubie3d.isAnimated())
        {
            glm::vec4 v4RotCenter( rubik3d.rot.center );
            glm::vec3 v3RotAxis( rubik3d.rot.axis );
            float angleRad = glm::radians(rubik3d.rot.angle);
            glm::mat4x4 matRot = glm::rotate( angleRad, v3RotAxis );
            position = rotateAround( position, v4RotCenter, matRot );
            cubieRotation = glm::rotate(angleRad, v3RotAxis) * cubieRotation ;
        }

        model = glm::translate(model, glm::vec3(position));
        model = model * cubieRotation;

        ourShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
    return (0);
}

int     Visualizer::drawLoop()
{
    float c = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        if (rubik3d.rot.isAnimated == false  && moveQueue.empty())
            break ;
        if ( !moveQueue.empty() && rubik3d.rot.isAnimated == false && glfwGetTime() - lastRotation > 0.075f && glfwGetTime() - c > 0.5f)
        {
            rubik3d.rotate(moveQueue.front());
            moveQueue.pop();
        }
        draw();
    }
    if (!glfwWindowShouldClose(window))
    {
        c = glfwGetTime();
        while (glfwGetTime() - c < 0.5f)
            draw();
    }
    return (0);
}

glm::vec4   Visualizer::rotateAround(  const glm::vec4& aPointToRotate, const glm::vec4& aRotationCenter, const glm::mat4x4& aRotationMatrix )
{
    glm::mat4x4 translate = 
        glm::translate( 
        glm::mat4(), 
        glm::vec3( aRotationCenter.x, aRotationCenter.y, aRotationCenter.z ) );
    glm::mat4x4 invTranslate = glm::inverse( translate );

    glm::mat4x4 transform = translate * aRotationMatrix * invTranslate;

    return transform * aPointToRotate;
}

void    Visualizer::processInput(GLFWwindow *window)
{
    Visualizer *ptr = (Visualizer *)glfwGetWindowUserPointer(window);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

static void    framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void    mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Visualizer *ptr = (Visualizer *)glfwGetWindowUserPointer(window);
    if (ptr->firstMouse)
    {
        ptr->lastX = xpos;
        ptr->lastY = ypos;
        ptr->firstMouse = false;
    }

    float xoffset = xpos - ptr->lastX;
    float yoffset = ptr->lastY - ypos;

    ptr->lastX = xpos;
    ptr->lastY = ypos;
}

static void     scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Visualizer *ptr = (Visualizer *)glfwGetWindowUserPointer(window);
}

static void     error_callback(int error, const char* description)
{
    std::cout << "Error: %s\n" << description << std::endl;
}

void window_close_callback(GLFWwindow* window)
{
    glfwSetWindowShouldClose(window, GLFW_FALSE);
}
