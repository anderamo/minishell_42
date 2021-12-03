/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:25:33 by aamorin-          #+#    #+#             */
/*   Updated: 2021/12/01 19:06:16 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_stdin_child(t_pipe *pipex, int i)
{
	if (pipex->exe[0].heredoc == 1)
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
	}
	return (1);
}

void	ft_stdout_child(t_pipe *pipex, int i)
{
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
}

void	close_child(t_pipe *pipex, int i, int j)
{
	while (j < pipex->procecess_num + 1)
	{
		if (j != i)
			close(pipex->pipes[j][0]);
		if (j != i + 1)
			close(pipex->pipes[j][1]);
		j++;
	}
	if (i != 0)
	{
		if (!(ft_stdin_child(pipex, i)))
		{
			g_mini.last_error = 127;
			exit (127);
		}
	}
	dup2(pipex->pipes[i][0], 0);
	close(pipex->pipes[i][0]);
	if (i != pipex->procecess_num - 1)
		ft_stdout_child(pipex, i);
	dup2(pipex->pipes[i + 1][1], 1);
	close(pipex->pipes[i + 1][1]);
}

void	close_father(t_pipe *pipex)
{
	int	j;
	int	i;
	int	status;

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
	while (1)
	{
		if (wait(&status) <= 0)
			break ;
	}
	wait (0);
	unlink("heredoc_tmp");
}
