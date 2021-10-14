#include "Visualizer.hpp"

Visualizer::Visualizer(const unsigned int& widht, const unsigned int& height) : ourShader()
{
    m_width = widht;
    m_height = height;
    init();
}

Visualizer::~Visualizer()
{
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &color_buffer);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

int     Visualizer::draw()
{
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        rubik3d.endRotation();


        // camera/view transformation
        glm::mat4 rubikRotation = rubik3d.getRotation();
        glm::mat4 view;
        glm::vec4 cameraPosition = glm::vec4(camera.GetPosition(), 1.0f);

        if (rubik3d.rot.isRotating)
        {
            float angleRad = glm::radians(rubik3d.rot.angle);
            glm::mat4x4 cameraMatRot = glm::rotate( angleRad, rubik3d.rot.axis );
            //cameraPosition = rotateAround( cameraPosition, rubik3d.rot.center, cameraMatRot );
            rubikRotation = glm::rotate(angleRad, rubik3d.rot.axis) * rubikRotation ;
        }
        view = glm::lookAt(glm::vec3(cameraPosition), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        view = view * rubikRotation;
        ourShader.setMat4("view", view);

        if (rubik3d.rot.isAnimated)
            rubik3d.rot.angle += ((rubik3d.rot.speed) * deltaTime);

        



        // render boxes
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

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return (0);
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

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(m_width, m_height, "Rubik", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)&(framebuffer_size_callback));
    glfwSetCursorPosCallback(window, (GLFWcursorposfun)&(mouse_callback));
    glfwSetScrollCallback(window, (GLFWscrollfun)&(scroll_callback));
    glfwSetErrorCallback((GLFWerrorfun)&error_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    ourShader = Shader("./resources/shaders/3.3.shader.vs", "./resources/shaders/3.3.shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
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

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), 0, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), ((void*)0));
    glEnableVertexAttribArray(1);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();

    return (0);
}

glm::vec4   Visualizer::rotateAround(  const glm::vec4& aPointToRotate, const glm::vec4& aRotationCenter, const glm::mat4x4& aRotationMatrix )
{
    glm::mat4x4 translate = 
        glm::translate( 
        glm::mat4(), 
        glm::vec3( aRotationCenter.x, aRotationCenter.y, aRotationCenter.z ) );
    glm::mat4x4 invTranslate = glm::inverse( translate );

    // The idea:
    // 1) Translate the object to the center
    // 2) Make the rotation
    // 3) Translate the object back to its original location

    glm::mat4x4 transform = translate * aRotationMatrix * invTranslate;

    return transform * aPointToRotate;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void    Visualizer::processInput(GLFWwindow *window)
{
    Visualizer *ptr = (Visualizer *)glfwGetWindowUserPointer(window);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    auto key_rotation = [&](int key_press, char key) {
        std::string s;
        s += key;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, key_press) == GLFW_PRESS)
        {   if ( ptr->rubik3d.rot.isAnimated == false ) ptr->rubik3d.rotate(s + "'"); }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && glfwGetKey(window, key_press) == GLFW_PRESS)
        {   if ( ptr->rubik3d.rot.isAnimated == false ) ptr->rubik3d.rotate(s + "2"); }
        else if (glfwGetKey(window, key_press) == GLFW_PRESS)
        {   if ( ptr->rubik3d.rot.isAnimated == false ) ptr->rubik3d.rotate(s); }
    };

    key_rotation(GLFW_KEY_KP_5, 'F');
    key_rotation(GLFW_KEY_KP_0, 'B');
    key_rotation(GLFW_KEY_KP_6, 'R');
    key_rotation(GLFW_KEY_KP_4, 'L');
    key_rotation(GLFW_KEY_KP_8, 'U');
    key_rotation(GLFW_KEY_KP_2, 'D');


    if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS)
    {   if ( ptr->rubik3d.rot.isAnimated == false ) ptr->rubik3d.rotate("Y"); }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {   if ( ptr->rubik3d.rot.isAnimated == false ) ptr->rubik3d.rotate("Y'"); }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {   if ( ptr->rubik3d.rot.isAnimated == false ) ptr->rubik3d.rotate("X'"); }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {   if ( ptr->rubik3d.rot.isAnimated == false ) ptr->rubik3d.rotate("X"); }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {   if ( ptr->rubik3d.rot.isAnimated == false ) ptr->rubik3d.rotate("Z'"); }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {   if ( ptr->rubik3d.rot.isAnimated == false ) ptr->rubik3d.rotate("Z"); }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
static void    framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
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
    float yoffset = ptr->lastY - ypos; // reversed since y-coordinates go from bottom to top

    ptr->lastX = xpos;
    ptr->lastY = ypos;

    ptr->camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
static void     scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Visualizer *ptr = (Visualizer *)glfwGetWindowUserPointer(window);
    ptr->camera.ProcessMouseScroll(yoffset);
}

static void     error_callback(int error, const char* description)
{
    std::cout << "Error: %s\n" << description << std::endl;
}