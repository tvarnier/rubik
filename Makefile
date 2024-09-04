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
			  Kociemba/Coordinates/cornerOrientation.cpp \
			  Kociemba/Coordinates/cornerPermutation.cpp \
			  Kociemba/Coordinates/edgeOrientation.cpp \
			  Kociemba/Coordinates/edgePermutation.cpp \
			  Kociemba/Coordinates/P2EdgePermutation.cpp \
			  Kociemba/Coordinates/P2UDSlice.cpp \
			  Kociemba/Coordinates/sliceSorted.cpp \
			  Kociemba/Coordinates/UDSlice.cpp \
			  Kociemba/Symmetries/cornerOrientation.cpp\
			  Kociemba/Symmetries/cornerPermutation.cpp\
			  Kociemba/Symmetries/Cubes.cpp\
			  Kociemba/Symmetries/flipUDSlice.cpp\
			  Kociemba/Symmetries/P2EdgePermutation.cpp\
			  Kociemba/MoveTables/cornerOrientation.cpp \
			  Kociemba/MoveTables/cornerPermutation.cpp \
			  Kociemba/MoveTables/edge8Perm.cpp \
			  Kociemba/MoveTables/edgeOrientation.cpp \
			  Kociemba/MoveTables/flipUDSlice.cpp \
			  Kociemba/MoveTables/P2EdgePermutation.cpp \
			  Kociemba/MoveTables/P2UDSlice.cpp \
			  Kociemba/MoveTables/sliceSorted.cpp \
			  Kociemba/MoveTables/UDSlice.cpp \
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
			  objects/Kociemba/Coordinates \
			  objects/Kociemba/MoveTables \
			  objects/Kociemba/Symmetries \
			  objects/Visualizer \
			  objects/Visualizer/Cubies3d \
			  objects/Visualizer/Rubik3d \
			  objects/RubikProgram

SRC_PATH	= ./srcs/
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
SRCS		+= $(addprefix $(SRC_PATH), $(OBJ_DIR), $(OBJ))

BIN			= $(SRC:%.cpp=%.o)
BIN			+= $(addprefix $(OBJ_DIR), $(OBJ:%.cpp=%.o))
BIN_PATH	= ./bins/
BINS		= $(addprefix $(BIN_PATH), $(BIN))
BIN_SUBDIR  	= $(addprefix $(BIN_PATH), $(OBJ_DIR))
BIN_SUBDIR  	+= $(addprefix $(BIN_PATH), $(OBJ_SUBDIR))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(BUILD_DIR) $(BIN_PATH) $(BIN_SUBDIR) $(BINS)
	$(CC) $(FLAGS) $(BINS) -lglfw -ldl -lX11 -o $@	

$(BIN_PATH):
	@ mkdir $@

$(BIN_SUBDIR):
	@ mkdir $@

$(BIN_PATH)%.o: $(SRC_PATH)%.cpp
	$(CC) -I includes -I external_lib -o $@ -c $< $(FLAGS)

clean:
	@ rm -rf $(BIN_PATH)

fclean: clean
	@ rm -f $(NAME)
	@ rm -rf $(BUILD_DIR)

re: fclean all
