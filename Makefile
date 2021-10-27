NAME		= rubik

OS := $(shell uname)

CC			= clang++ -std=c++2a
FLAGS		= -O3 -pthread -g

INCLUDES	= ./includes/rubik.hpp

SRC			= main.cpp \
			  parser.cpp

OBJ			= Cube/Cube.cpp \
			  Cube/CubeMovement.cpp \
			  Kociemba/Kociemba.cpp \
			  Kociemba/KociembaCoordinates.cpp \
			  Kociemba/KociembaSymmetries.cpp \
			  Kociemba/KociembaMoveTables.cpp \
			  Kociemba/KociembaPruneTables.cpp \
			  Kociemba/KociembaDepht.cpp \
			  Kociemba/KociembaSolve.cpp \
			  Visualizer/glad.cpp \
			  Visualizer/Visualizer.cpp \
			  Visualizer/Rubik3d/Rubik3d.cpp \
			  Visualizer/Rubik3d/Rubik3dMovements.cpp

OBJ_DIR		= objects/
OBJ_SUBDIR	= objects/Cube \
			  objects/Kociemba \
			  objects/Visualizer \
			  objects/Visualizer/Cubies3d \
			  objects/Visualizer/Rubik3d \
			  objects/RubikProgram

BUILD_DIR	= ./build/
BUILD_MAKE	= 

SRC_PATH	= ./srcs/
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
SRCS		+= $(addprefix $(SRC_PATH), $(OBJ_DIR), $(OBJ))

BIN			= $(SRC:%.cpp=%.o)
BIN			+= $(addprefix $(OBJ_DIR), $(OBJ:%.cpp=%.o))
BIN_PATH	= ./bins/
BINS		= $(addprefix $(BIN_PATH), $(BIN))
BIN_SUBDIR  = $(addprefix $(BIN_PATH), $(OBJ_DIR))
BIN_SUBDIR  += $(addprefix $(BIN_PATH), $(OBJ_SUBDIR))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(BUILD_DIR) $(BIN_PATH) $(BIN_SUBDIR) $(BINS)
ifeq ($(OS), Darwin)
	$(CC)  $(FLAGS) $(BINS) ./build/src/libglfw3.a -ldl -framework Cocoa -framework OpenGL -framework IOKit -o $@
else
	$(CC) $(FLAGS) $(BINS) ./build/src/libglfw3.a -ldl -lX11 -o $@
endif
	

$(BIN_PATH):
	@ mkdir $@

$(BIN_SUBDIR):
	@ mkdir $@

$(BIN_PATH)%.o: $(SRC_PATH)%.cpp
	$(CC) -I includes -o $@ -c $< $(FLAGS)

$(BUILD_DIR):
	@ mkdir $@
	cmake -S ./external_lib/glfw/ -B $(BUILD_DIR)
	make -C $(BUILD_DIR)

clean:
	@ rm -rf $(BIN_PATH)

fclean: clean
	@ rm -f $(NAME)
	@ rm -rf $(BUILD_DIR)

re: fclean all
