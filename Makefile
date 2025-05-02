NAME = Famine

CC = cc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

SRC = famine.c \
	  folder_iter.c \
	  main.c

SRC_BONUS = famine_bonus.c \
	  folder_iter_bonus.c \
	  main_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	echo "./Famine created"

bonus: $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)
	echo "./Famine created"

clean:
		rm -f $(OBJ) $(OBJ_BONUS)
		echo "OBJ deleted"

fclean: clean
		rm -f $(NAME)
		echo "$(NAME) deleted"

re: fclean all

run: re
	./Famine

run_bonus: fclean bonus
			./Famine

.SILENT:

.PHONY: all clean fclean re run bonus run_bonus