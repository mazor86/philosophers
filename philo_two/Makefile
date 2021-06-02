NAME = philo_two
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = main.c init.c action.c utils.c routines.c print_message.c utils2.c
OBJ = $(SRCS:.c=.o)

HEADER = philo_two.h

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c -o $@ $< -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norminette:
	@norminette $(SRCS) $(HEADER)

.PHONY: all clean fclean re norminette NONE