NAME		= rubik

CC			= clang++ -std=c++20
FLAGS		= -O3 -pthread
LIB			= lib/lib.a

FRAMEWORKS  = -framework Cocoa -framework OpenGL -framework IOKit

INCLUDES	= ./includes/rubik.hpp

SRC			= main.cpp

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
			  Visualizer/Rubik3d/Rubik3dMovements.cpp \
			  RubikProgram/RubikProgram.cpp

OBJ_DIR		= objects/
OBJ_SUBDIR	= objects/Cube \
			  objects/Kociemba \
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
BIN_SUBDIR  = $(addprefix $(BIN_PATH), $(OBJ_DIR))
BIN_SUBDIR  += $(addprefix $(BIN_PATH), $(OBJ_SUBDIR))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(BIN_PATH) $(BIN_SUBDIR) $(BINS)
	$(CC) $(pkg-config --cflags glfw3 gl) $(FLAGS) $(BINS) ./build/src/libglfw3.a -ldl -o $@

$(BIN_PATH):
	@ mkdir $@

$(BIN_SUBDIR):
	 mkdir $@

$(BIN_PATH)%.o: $(SRC_PATH)%.cpp
	$(CC) -I includes -o $@ -c $< $(FLAGS)

clean:
	@ rm -rf $(BIN_PATH)

fclean: clean
	@ rm -f $(NAME)

re: fclean all
