/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:46:00 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/29 10:13:13 by aamorin-         ###   ########.fr       */
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
	char	*stdin_file;
	char	*stdout_file;
	int		append;
	int		heredoc;
}	t_exe;

typedef struct s_pipe
{
	int		**pipes;
	int		*pid;
	int		procecess_num;
	char	**com;
	char	*stdin_file;
	char	*stdout_file;
	char	*tomas;
	t_exe	*exe;
	char	*bin;
}	t_pipe;

typedef struct s_command
{
	int		options;
	int		dollar_fail;
	char	**args;
}	t_cmd;

typedef struct s_mini
{
	char	**s_pipe;
	char	**env;
	char	*path;
	int		last_error;
	char	*prompt;
	char	*line;
	pid_t	pid;
	char	*error;
	int		fd;
	int		stop;
}	t_mini;

t_mini	g_mini;

void	write_pwd(void);
int		init_env(char **env);
size_t	ft_array_size(char **arr);
int		ft_frlloc(char **tab);
void	ft_frlloc_n(char **tab, size_t n);
void	free_proc(t_pipe *pipex);
int		ft_setenv(char *name, char *value, int replace);
char	*ft_getenv(char *name);
char	*ft_strjoin3(char *a, char *b, char *c);
int		ft_print_env(void);
char	*find_env(char *src, int i);
void	ft_pwd(int print);
int		ft_copy_quote(char **commands, t_cmd *cmd, size_t i, int j);
int		ft_dollar(t_cmd *cmd, char *src, char c, int j);
int		parse_arguments(t_cmd *cmd);
int		check_if_exits(t_pipe pipex, int a);
char	**ft_frlloc_int(int **tab, int size);
void	signal_proc(void);
int		builtins(char **commands);
void	ft_cd_old_pwd(int i);
void	ft_cd(char *next_path, int i);
void	pipex(char **argv, int count, int a, int index);
char	*readline(const char *prompt);
void	ft_heredoc(char *del);
void	ft_action(int sig);
int		builtins_no_pipe(char *line, char **commands);
int		ft_arraybilen(char **array);
int		ft_last_error(void);
char	*get_bin_path(char **envp, char *command);
int		get_path(char **envp);
void	create_processes(t_pipe pipex, int i);
void	ft_heredoc(char *del);
void	child(t_pipe pipex, char **envp, int i, int j);
int		pipex_3(t_pipe *pipex, int index, int a);
int		env_len(const char *str, int pos);
int		ft_stdin_file(t_pipe *pipex, int i);
void	ft_stdout_file_2(t_pipe *pipex, int i);
int		ft_stdin_file_2(t_pipe *pipex, int i);
void	free_pipex(t_pipe *pipex);
void	free_processes(t_pipe *pipex);
int		free_builtins(t_cmd	*cmd);
t_pipe	init_pipex(int a, int i);
int		pipex_4(t_pipe *pipex, int po);
void	close_child(t_pipe *pipex, int i, int j);
void	close_father(t_pipe *pipex);

#endif
