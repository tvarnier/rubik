NAME		= rubik

CC			= clang++ -std=c++17
FLAGS		= -O3
LIB			= lib/lib.a

INCLUDES	= ./includes/rubik.hpp

SRC			= main.cpp

OBJ			= Cube/Cube.cpp \
			  Cube/CubeMovement.cpp \
			  Kociemba/Kociemba.cpp \
			  Kociemba/KociembaCoordinates.cpp \
			  Kociemba/KociembaSymmetries.cpp \
			  Kociemba/KociembaMoveTables.cpp \
			  Kociemba/KociembaPruneTables.cpp \
			  Kociemba/KociembaDepht.cpp
OBJ_DIR		= objects/
OBJ_SUBDIR	= objects/Cube \
			  objects/Kociemba

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
	$(CC) $(FLAGS) $(BINS) $(LIB) -o $@

$(BIN_PATH):
	@ mkdir $@

$(BIN_SUBDIR):
	 mkdir $@

$(LIB):
	@ make -C lib

$(BIN_PATH)%.o: $(SRC_PATH)%.cpp
	$(CC) -I includes -o $@ -c $< $(FLAGS)

clean:
	@ make -C lib clean
	@ rm -rf $(BIN_PATH)

fclean: clean
	@ rm -rf $(LIB)
	@ rm -f $(NAME)

re: fclean all
