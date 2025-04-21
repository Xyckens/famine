NAME = Famine

CC = cc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address


SRC = famine.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)
	echo "./Famine created"

clean:
		rm -f $(OBJ)
		echo "OBJ deleted"

fclean: clean
		rm -f $(NAME)
		echo "$(NAME) deleted"

re: fclean all

run: re
	./Famine

.SILENT:

.PHONY: all, clean, fclean, re