/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:46:00 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/11 17:52:08 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf/includes/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFF 1024

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
	char	**com;
	int		append;
	int		heredoc;
	t_exe	*exe;
	char	*bin;
}	t_pipe;

typedef struct s_command
{
	char	*line;
	int		options;
	char	**args;
}	t_cmd;

typedef struct s_mini
{
	char	**env;
	char	*path;
	int		last_error;
	char	*line;
}	t_mini;

t_mini	g_mini;

void	write_pwd(void);
int		init_env(char **env);
size_t	ft_array_size(char **arr);
char	**ft_frlloc(char **tab);
void	ft_frlloc_n(char **tab, size_t n);
int		ft_setenv(char *name, char *value, int replace);
char	*ft_getenv(char *name);
void	ft_print_env(void);
void	ft_pwd(int print);
int		copy_quote(char *dest, char *src, int i);
int		parse_arguments(t_cmd *cmd);
int		check_if_exits(t_pipe pipex, int a);
char	**ft_frlloc_int(int **tab, int size);
void	signal_proc(void);
int		builtins(char **commands);
void	pipex(char **argv, int count, int a);
int		builtins_no_pipe(char *line);
char	*readline(const char *prompt);
void	ft_heredoc(char *del);
void	ft_action(int sig);
int		builtins_no_pipe(char *line);
int		ft_arraybilen(char **array);
char	*get_bin_path(char **envp, char *command);
int		get_path(char **envp);
void	create_processes(t_pipe pipex);
void	ft_heredoc(char *del);
void	child(t_pipe pipex, char **envp, int i, int j);
int		pipex_3(t_pipe *pipex, int index);
int		ft_stdin_file(t_pipe *pipex);

#endif
