NAME = ircserv
BONUS = bot_client
CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address
SRC = $(addprefix ./, Client.cpp main.cpp Server.cpp Toolkit.cpp Channel.cpp Member.cpp Parse.cpp  )
BONUS_SRC = bot/Bot.cpp bot/main.cpp Toolkit.cpp Client.cpp
OBJ = $(SRC:.cpp=.o)
BONUS_OBJ = $(BONUS_SRC:.cpp=.o)

.PHONY: all clean fclean re

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(SRC) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@

$(BONUS): $(BONUS_SRC) $(BONUS_OBJ)
	$(CC) $(FLAGS) $(BONUS_SRC) -o $@

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	rm -rf $(BONUS_OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BONUS)

re: fclean all bonus
