NAME		= learnOpenGl

CC			= clang++ -std=c++17
FLAGS		= -O3

INCLUDES	= ./includes/learnOpenGl.hpp

SRC			= main.cpp \
			  glad.cpp

OBJ			= Rubik3d/Rubik3d.cpp \
			  Rubik3d/Rubik3dMovements.cpp \
			  Visualizer/Visualizer.cpp
OBJ_DIR		= objects/
OBJ_SUBDIR	= objects/Cubies3d \
			  objects/Rubik3d \
			  objects/Visualizer

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

$(NAME): $(LIB) $(BIN_PATH) $(BIN_SUBDIR) $(BINS)
	$(CC) $(FLAGS) $(BINS) -framework Cocoa -framework OpenGL -framework IOKit -L/Users/tvarnier/.brew/lib -lglfw.3 -o $@

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
