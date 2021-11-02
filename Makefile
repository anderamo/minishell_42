NAME = minishell

MANDATORY	=	main.c

OBJ_1 = $(MANDATORY:.c=.o)

CC = gcc

INC_1 = -I./includes

#FLAGS	= -Wall -Wextra -Werror

SANITIZE	= -fsanitize=address -g3

all: $(NAME)

$(NAME): $(OBJ_1)
		$(MAKE) -C ./ft_printf
		cp ft_printf/libftprintf.a .
		$(CC) $(FLAGS) $(INC_1) $(MANDATORY) -lreadline libftprintf.a -o $(NAME)

s:
	$(CC) $(INC_1) $(MANDATORY) $(SANITIZE) -lreadline libftprintf.a -o $(NAME)
f:
	$(CC) $(INC_1) $(MANDATORY) -lreadline libftprintf.a -o $(NAME)

clean:
	$(MAKE) clean -C ./ft_printf
	rm -rf *.o
	rm -rf a.out
	rm -rf a.out*

fclean: clean
	$(MAKE) fclean -C ./ft_printf
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf *.a

re: fclean all

.PHONY:	all clean fclean bonus re
