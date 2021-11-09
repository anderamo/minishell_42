/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:46:00 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/09 17:47:02 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf/includes/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "../readline/include/readline/readline.h"
# include "../readline/include/readline/history.h"

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_exe
{
	char	**c_split;
}	t_exe;

typedef struct s_pipe
{
	int		**pipes;
	int		*pid;
	int		procecess_num;
	char	*stdin_file;
	char	*stdout_file;
	int		append;
	int		heredoc;
	t_exe	*exe;
	char	*bin;
}	t_pipe;

typedef struct s_mini
{
	char	**env;
	char	*path;
	char	*last_argument;
	char	*current_dir;
} t_mini;

t_mini g_mini;

void	write_pwd();
int		init_env(char **env);
size_t	ft_array_size(char **arr);
char	**ft_frlloc(char **tab);
void	ft_frlloc_n(char **tab, size_t n);
int		ft_setenv(char *name, char *value, int replace);
void	ft_print_env(void);
void    ft_pwd(int print);
void	signal_proc();
int		builtins(char **commands);
int		builtins_no_pipe(char *line);
char	*readline(const char *prompt);
void	ft_action(int sig);

#endif
