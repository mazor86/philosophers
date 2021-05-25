NAME = philo_one
CC = gcc -O2
FLAGS = -Wall -Wextra -Werror

SRCS = main.c init.c eating.c utils.c waiter.c
OBJ = $(SRCS:.c=.o)

HEADER = philo_one.h

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c -o $@ $< -g

all: $(NAME)

$(NAME): $(OBJ)
	@echo "compile ..."
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	@echo "clean minishell object files..."
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norminette:
	@norminette $(SRCS) $(HEADER)

.PHONY: all clean fclean re norminette NONE