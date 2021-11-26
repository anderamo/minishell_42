/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:34:40 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/26 17:37:35 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_commas(t_pipe *pipex, int i, int j)
{
	char	*c;

	if (ft_strcmp(pipex->exe[i].c_split[j], "awk")
		|| ft_strcmp(pipex->exe[i].c_split[j], "echo"))
	{
		j++;
		while ((int)ft_array_size(pipex->exe[i].c_split) > j)
		{
			if (pipex->exe[i].c_split[j][0] == '\"'
					|| pipex->exe[i].c_split[j][0] == '\'')
			{
				c = malloc(sizeof(char) * (2));
				c[0] = pipex->exe[i].c_split[j][0];
				c[1] = '\0';
				pipex->exe[i].c_split[j]
					= ft_strtrim(pipex->exe[i].c_split[j], c);
			}
			j++;
		}
	}
}

void	child(t_pipe pipex, char **envp, int i, int j)
{
	close_child(&pipex, i, j);
	pipex.bin = get_bin_path(envp, pipex.exe[i].c_split[0]);
	if (!builtins(pipex.exe[i].c_split))
	{
		delete_commas(&pipex, i, j);
		if (execve(pipex.bin, pipex.exe[i].c_split, envp) == -1)
			printf ("bash: %s: command not found\n", pipex.exe[i].c_split[0]);
	}
	free(pipex.bin);
	g_mini.last_error = 127;
	exit (127);
}

int	ft_stdin_file(t_pipe *pipex, int i)
{
	close(pipex->pipes[i][0]);
	if (pipex->exe[i].heredoc == 1)
		pipex->pipes[i][0] = open("heredoc_tmp", O_RDONLY);
	else
	{
		if (pipex->exe[i].stdin_file != NULL)
		{
			pipex->pipes[i][0] = open(pipex->exe[i].stdin_file, O_RDONLY);
			if (pipex->pipes[i][0] < 0)
			{
				printf("bash: %s: No such file or directory\n",
					pipex->exe[i].stdin_file);
				free(pipex->exe[i].stdin_file);
				g_mini.last_error = 1;
				return (0);
			}
			free(pipex->exe[i].stdin_file);
		}
		else
			pipex->pipes[i][0] = open(pipex->exe[i].stdin_file, O_RDONLY);
	}
	return (1);
}

void	ft_stdout_file(t_pipe *pipex, int i)
{
	if (pipex->exe[0].heredoc == 1 && pipex->exe[0].c_split == NULL)
		pipex->exe[0].c_split = ft_split_minishell("cat");
	close(pipex->pipes[i + 1][1]);
	if (pipex->exe[i].stdout_file != NULL)
	{
		if (pipex->exe[i].append == 1)
			pipex->pipes[i + 1][1]
				= open(pipex->exe[i].stdout_file,
					O_RDWR | O_APPEND | O_CREAT, 0755);
		else
			pipex->pipes[i + 1][1]
				= open(pipex->exe[i].stdout_file,
					O_RDWR | O_TRUNC | O_CREAT, 0755);
		free(pipex->exe[i].stdout_file);
	}
	else
		pipex->pipes[i + 1][1]
			= open(pipex->exe[i].stdout_file,
				O_RDONLY);
}

void	create_processes(t_pipe pipex, int i)
{
	while (++i < pipex.procecess_num)
	{
		if (!(ft_stdin_file(&pipex, i)))
			return ;
		ft_stdout_file(&pipex, i);
	}
	i = -1;
	while (++i < pipex.procecess_num)
	{
		pipex.pid[i] = fork();
		g_mini.pid = pipex.pid[i];
		if (pipex.pid[i] == -1)
			break ;
		if (pipex.pid[i] == 0)
			child(pipex, g_mini.env, i, 0);
	}
	close_father(&pipex);
	wait (0);
	free_processes(&pipex);
	g_mini.pid = 0;
	unlink("heredoc_tmp");
}
