// clang++ -std=c++2a -O3 -pthread -g tests/basicGLFW.cpp ./srcs/objects/Visualizer/glad.cpp ./build/src/libglfw3.a -ldl -framework Cocoa -framework OpenGL -framework IOKit -o test -I includes
// clang++ -std=c++2a -O3 -pthread -g tests/basicGLFW.cpp ./srcs/objects/Visualizer/glad.cpp ./build/src/libglfw3.a -ldl -lX11 -o test -I includes

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=no --show-possibly-lost=no ./test

#include "VisualizerIncludes.hpp"

int main(int, char**)
{
    glfwInit();
    auto window = glfwCreateWindow(640,480,"Title",NULL,NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    glfwDestroyWindow(window);
    glfwTerminate();
}