NAME		= lib.a

CC			= ~/.brew/bin/g++-9
FLAGS		= -g -Wall -Wextra -Werror

INCLUDES	= ./includes/lib.hpp

MATH		= fabs.cpp \
			  floor.cpp \
			  frexp.cpp \
			  ldexp.cpp \
			  pgcd.cpp \
			  pow.cpp \
			  sqrt.cpp

STRING		= count_char.cpp

SRC_CAT 	= math string
SRCS		= $(addprefix math/, $(MATH))
SRCS		+= $(addprefix string/, $(STRING))


BIN			= $(SRCS:%.cpp=%.o)
BIN_PATH	= bins
BIN_CAT 	= $(addprefix $(BIN_PATH)/, $(SRC_CAT))
BINS		= $(addprefix $(BIN_PATH)/, $(BIN))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(BIN_PATH) $(BIN_CAT) $(BINS)
	@ ar rc $(NAME) $(BINS)
	@ echo "   ** LIB COMPILED **"

$(BIN_PATH):
	@ mkdir $@

$(BIN_CAT):
	@ mkdir $@

$(BIN_PATH)/%.o: %.cpp $(HEADER)
	@ $(CC) -I includes -o $@ -c $< $(FLAGS)

clean:
	@ rm -rf $(BIN_PATH)

fclean: clean
	@ rm -f $(NAME)

re: fclean all
