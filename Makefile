NAME = ircserv
CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address
SRC = $(addprefix ./, Client.cpp main.cpp Server.cpp Toolkit.cpp Parse.cpp )
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
