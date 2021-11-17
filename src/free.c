/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:11:42 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/17 19:14:53 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipex(t_pipe *pipex)
{
	if (pipex->tomas)
		free(pipex->tomas);
	ft_frlloc(pipex->com);
}

int	free_builtins(t_cmd	*cmd)
{
	free(cmd->line);
	free(cmd);
	free(g_mini.error);
	return (1);
}

void	free_processes(t_pipe *pipex)
{
	int	i;

	i = -1;
	free(pipex->pid);
	while (++i < pipex->procecess_num)
		ft_frlloc(pipex->exe[i].c_split);
	ft_frlloc_int(pipex->pipes, pipex->procecess_num + 1);
	free(pipex->exe);
}
