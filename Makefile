NAME = minishell

MANDATORY	=	main.c\
				src/signal.c\
				src/builtins.c\
				src/builtins_no_pipe.c\
				src/builtin_env.c\
				src/env.c\
				src/pipex.c\
				src/pipex_2.c\
				src/pipex_processes.c\
				src/array.c\
				src/heredoc.c\
				src/arguments.c\
				src/free.c

CC = gcc

INC_1 = -I./includes/ -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

FLAGS	= -Wall -Wextra -Werror

SANITIZE	= -fsanitize=address -g3

$(NAME):
		$(MAKE) -C ./ft_printf
		cp ft_printf/libftprintf.a .
		$(CC) $(FLAGS) $(INC_1) $(MANDATORY) -lreadline libftprintf.a -o $(NAME)

all: $(NAME)

s:
	$(CC) $(INC_1) $(MANDATORY) $(SANITIZE) -lreadline libftprintf.a -o $(NAME)
f:
	$(CC) $(INC_1) $(MANDATORY) -lreadline libftprintf.a -o $(NAME)
v:
	$(CC) $(INC_1) $(MANDATORY) -lreadline libftprintf.a -o $(NAME)
	valgrind --leak-check=full ./minishell

clean:
	$(MAKE) clean -C ./ft_printf
	rm -rf *.o
	rm -rf .DS_Store
	rm -rf a.out
	rm -rf a.out*

fclean: clean
	$(MAKE) fclean -C ./ft_printf
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf *.a

re: fclean all

.PHONY:	all clean fclean bonus re
