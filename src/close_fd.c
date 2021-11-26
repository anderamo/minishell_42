/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:25:33 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/26 17:21:38 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	dup2(pipex->pipes[i][0], 0);
	close(pipex->pipes[i][0]);
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
}
