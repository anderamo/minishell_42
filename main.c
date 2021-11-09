/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:45:25 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/09 19:11:45 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_arraybilen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**ft_frlloc_int(int **tab, int size)
{
	int	i;

	i = 0;
	while (size > i)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	get_path(char **envp)
{
	int		i;
	char	**split;

	i = 0;
	while (1)
	{
		split = ft_split(envp[i], '=');
		if (!strcmp(split[0], "PATH"))
			break ;
		ft_frlloc(split);
		i++;
	}
	ft_frlloc(split);
	return (i);
}

char	*get_bin_path(char **envp, char *command)
{
	char	**path_split;
	int		i;
	int		j;

	i = get_path(envp);
	j = 0;
	path_split = ft_split(envp[i] + 5, ':');
	while (path_split[j])
	{
		path_split[j] = ft_strjoin(path_split[j], "/");
		path_split[j] = ft_strjoin(path_split[j], command);
		if (!access(path_split[j], F_OK))
			return (path_split[j]);
		j++;
	}
	ft_frlloc(path_split);
	return (NULL);
}

t_pipe	init_pipex(int a)
{
	t_pipe	pipex;
	int		i;

	pipex.procecess_num = a;
	pipex.pipes = (int **)malloc((pipex.procecess_num + 1) * sizeof(int *));
	pipex.exe = (t_exe *)malloc((pipex.procecess_num + 1) * sizeof(t_exe));
	pipex.pid = (int *)malloc((pipex.procecess_num) * sizeof(int));
	i = 0;
	while (i < pipex.procecess_num + 1)
	{
		pipex.pipes[i] = (int *)malloc((2) * sizeof(int));
		i++;
	}
	i = 0;
	while (i < pipex.procecess_num + 1)
	{
		if (pipe(pipex.pipes[i]) == -1)
			exit (0);
		i++;
	}
	return (pipex);
}

void	child(t_pipe pipex, char **envp, int i)
{
	int		j;

	j = 0;
	while (j < pipex.procecess_num + 1)
	{
		if (j != i)
			close(pipex.pipes[j][0]);
		if (j != i + 1)
			close(pipex.pipes[j][1]);
		j++;
	}
	dup2(pipex.pipes[i][0], 0);
	close(pipex.pipes[i][0]);
	dup2(pipex.pipes[i + 1][1], 1);
	close(pipex.pipes[i + 1][1]);
	pipex.bin = get_bin_path(envp, pipex.exe[i].c_split[0]);
	if (!builtins(pipex.exe[i].c_split))
	{
		if (execve(pipex.bin, pipex.exe[i].c_split, envp) == -1)
		{
			//ft_frlloc(pipex.c_split);
			free(pipex.bin);
			perror("execve");
			exit (127);
		}
	}
	exit (127);
}

int	shell(char **commands)
{
	char	*bin;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		bin = get_bin_path(g_mini.env, commands[0]);
		if (execve(bin, commands, g_mini.env) == -1)
		{
			perror("execve");
			ft_frlloc(commands);
			free(bin);
			exit (127);
		}
	}
	else if (pid > 0)
	{
		wait(0);
		return (1);
	}
	else if (pid < 0)
		return (0);
	return (1);
}

int count_pipes(char **argv)
{
	int index;
	int i;

	index = 0;
	i = 0;
	while (argv[index])
	{
		if (!ft_strcmp(argv[index], "|"))
			i++;
		index++;
	}
	ft_printf("pipes = %d &&&&&&&& process = %d\n", i + 1, i);
	return (i + 1);
}

void	pipex_2(t_pipe pipex)
{
	int		i;

	i = 0;
	close(pipex.pipes[0][0]);
	if (pipex.heredoc == 1)
		pipex.pipes[0][0] = open("heredoc_tmp", O_RDONLY);
	else
		pipex.pipes[0][0] = open(pipex.stdin_file, O_RDONLY);
	close(pipex.pipes[pipex.procecess_num][1]);
	if (pipex.stdout_file != NULL)
	{
		if (pipex.append == 1)
			pipex.pipes[pipex.procecess_num][1] = open(pipex.stdout_file, O_RDWR | O_APPEND | O_CREAT, 0644);
		else
			pipex.pipes[pipex.procecess_num][1] = open(pipex.stdout_file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	while (i < pipex.procecess_num)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] == -1)
		{
			wait (0);
			break ;
		}
		if (pipex.pid[i] == 0)
		{
			child(pipex, g_mini.env, i);
		}
		i++;
	}
	free(pipex.pid);
	ft_frlloc_int(pipex.pipes, pipex.procecess_num + 1);

}

void	ft_heredoc(char *delimitador)
{
	char	*line;
	int		fd;

	fd = open("heredoc_tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		line = readline("\033[36m> \033[0m");
		if (!ft_strcmp(line, delimitador))
				break ;
		write (fd, line, ft_strlen(line));
		write (fd, "\n", 1);
	}
}

void	pipex(char **argv, int count)
{
	t_pipe	pipex;
	int		i;
	int		a;
	int		index;
	char	**command;

	/*
	index = 0;
	ft_printf("------------SPLIT------------\n");
	while (argv[index])
	{
		ft_printf("%s\n", argv[index]);
		index++;
	}
	ft_printf("-----------------------------\n");
	*/
	index = 0;
	a = 0;
	pipex = init_pipex(count);
	pipex.stdin_file = NULL;
	pipex.stdout_file = NULL;
	pipex.exe[0].c_split = NULL;
	pipex.append = 0;
	pipex.heredoc = 0;
	while (argv[a])
	{
		command = ft_split(argv[a], ' ');
		index = 0;
		while (ft_arraybilen(command) > index && command[index])
		{
				if (!ft_strcmp(command[index], ">"))
				{
					//ft_printf("Stdout es %s borrando lo que hay dentro(en caso de no exista lo crea)\n", command[index + 1]);
					pipex.stdout_file = ft_strdup(command[index + 1]);
					pipex.append = 0;
					index += 2;
				}
				else if (ft_arraybilen(command) > index && !ft_strcmp(command[index], ">>"))
				{
					//ft_printf("Stdout es %s borrando lo que hay dentro(en caso de no exista lo crea)\n", command[index + 1]);
					pipex.stdout_file = ft_strdup(command[index + 1]);
					pipex.append = 1;
					index += 2;
				}
				else if (ft_arraybilen(command) > index && !ft_strcmp(command[index], "<<"))
				{
					if (ft_arraybilen(command) > index + 1)
					{
						ft_heredoc(command[++index]);
						pipex.heredoc = 1;
					}
					else
					{
						printf("bash: syntax error near unexpected token `newline'");
						return ;
					}
					index++;
				}
				else if (ft_arraybilen(command) > index && !ft_strcmp(command[index], "<"))
				{
					//ft_printf("Stdin es %s\n", command[index + 1]);
					pipex.stdin_file = ft_strdup(command[index + 1]);
					index++;
					if (ft_arraybilen(command) < index + 1)
					{
						if (ft_strcmp(command[index + 1], ">") || ft_strcmp(command[index + 1], "<")
							|| ft_strcmp(command[index + 1], "<<") || ft_strcmp(command[index + 1], ">>"))
						{
							//ft_printf(" %s\n", command[index + 1]);
							index++;
						}
					}
					index++;
				}
				else
				{
					//ft_printf("command es %s\n", command[index]);
					if ((!ft_strcmp(command[index],"echo") || !ft_strcmp(command[index],"grep") || !ft_strcmp(command[index],"cd")
						|| !ft_strcmp(command[index],"cat") || !ft_strcmp(command[index],"ls") || !ft_strcmp(command[index],"rm")
						|| !ft_strcmp(command[index],"rm") || !ft_strcmp(command[index],"pwd")) && ft_arraybilen(command) > index + 1)
					{
						i = index;
						while (ft_arraybilen(command) > index + 1 && ft_strcmp(command[index + 1], "<") && ft_strcmp(command[index + 1], ">")
							&& ft_strcmp(command[index + 1], "<<") && ft_strcmp(command[index + 1], ">>"))
						{
							command[i] = ft_strjoin_space(command[i], command[index + 1]);
							index++;
						}
						//ft_printf("join = %s\n", command[i]);
						pipex.exe[a].c_split = ft_split(command[i], ' ');
					}
					else
						pipex.exe[a].c_split = ft_split(command[index], ' ');

					if (ft_arraybilen(command) > index + 1 && ft_strcmp(command[index + 1], "<")
					&& ft_strcmp(command[index + 1], "<<") && ft_strcmp(command[index + 1], ">")
					&& ft_strcmp(command[index + 1], ">>"))
					{
						//ft_printf("Stdin es %s\n", command[index + 1]);
						pipex.stdin_file = ft_strdup(command[index + 1]);
						index += 2;

					}
						index++;
				}
				}
			ft_frlloc(command);
			a++;
	}
	if (pipex.exe[0].c_split != NULL)
		pipex_2(pipex);
	if (pipex.heredoc == 1)
		unlink("heredoc_tmp");
	ft_frlloc(argv);
}

void	write_pwd()
{
	int		i;
	char	**split;

	i = 0;
	while (g_mini.env[i])
	{
		split = ft_split(g_mini.env[i], '=');
		if (!strcmp(split[0], "PWD"))
			break;
		ft_frlloc(split);
		i++;
	}
	printf("\033[36m%s\n", split[1]);
	ft_frlloc(split);
}


/////HACER ARRAY DE STRUC CON LOS COMANDOS///
int	main(int a, char **argv, char **env)
{
	char		*line;
	char		**split_pipe;

	(void) a;
	(void) argv;
	init_env(env);
	signal_proc();
	while (1)
	{
		wait (0);
		write_pwd();
		line = readline(" > \033[0m");
		if (!line)
			exit(1);
		if (!ft_strcmp(line, "exit"))
			break ;
		if (!builtins_no_pipe(line))
		{
			if (ft_strcmp(line, ""))
			{
				add_history(line);
				split_pipe = ft_split(line, '|');
				pipex(split_pipe, ft_arraybilen(split_pipe));
			}
		}
		free(line);
	}
	return (0);
}
