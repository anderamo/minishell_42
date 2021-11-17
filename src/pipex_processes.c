/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:34:40 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/17 19:54:45 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_pipe pipex, char **envp, int i, int j)
{
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
			printf ("bash: %s: command not found\n", pipex.exe[i].c_split[0]);
	}
	free(pipex.bin);
	g_mini.last_error = 127;
	exit (127);
}

int	ft_stdin_file(t_pipe *pipex)
{
	close(pipex->pipes[0][0]);
	if (pipex->heredoc == 1)
		pipex->pipes[0][0] = open("heredoc_tmp", O_RDONLY);
	else
	{
		if (pipex->stdin_file != NULL)
		{
			pipex->pipes[0][0] = open(pipex->stdin_file, O_RDONLY);
			if (pipex->pipes[0][0] < 0)
			{
				printf("bash: %s: No such file or directory\n",
					pipex->stdin_file);
				free(pipex->stdin_file);
				g_mini.last_error = 1;
				return (0);
			}
			free(pipex->stdin_file);
		}
		else
			pipex->pipes[0][0] = open(pipex->stdin_file, O_RDONLY);
	}
	return (1);
}

void	ft_stdout_file(t_pipe *pipex)
{
	close(pipex->pipes[pipex->procecess_num][1]);
	if (pipex->stdout_file != NULL)
	{
		if (pipex->append == 1)
			pipex->pipes[pipex->procecess_num][1] = open(pipex->stdout_file,
					O_RDWR | O_APPEND | O_CREAT, 0755);
		else
			pipex->pipes[pipex->procecess_num][1] = open(pipex->stdout_file,
					O_RDWR | O_TRUNC | O_CREAT, 0755);
		free(pipex->stdout_file);
	}
	else
		pipex->pipes[pipex->procecess_num][1] = open(pipex->stdout_file,
				O_RDONLY);
}

void	close_father(t_pipe *pipex)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (j < pipex->procecess_num + 1)
	{
		close(pipex->pipes[j][1]);
		if (j != 0)
			close(pipex->pipes[j][0]);
			j++;
	}
	if (!ft_strcmp(pipex->exe[i].c_split[0], "$?"))
		g_mini.last_error = 127;
}

void	create_processes(t_pipe pipex)
{
	int		i;

	if (!(ft_stdin_file(&pipex)))
		return ;
	ft_stdout_file(&pipex);
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
	if (pipex.heredoc == 1)
		unlink("heredoc_tmp");
}
