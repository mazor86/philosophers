NAME = philo_one
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = main.c init.c eating.c utils.c monitor.c print_message.c
OBJ = $(SRCS:.c=.o)

HEADER = philo_one.h

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c -o $@ $<

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

.PHONY: all clean fclean re norminette
