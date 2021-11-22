/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:25:18 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/22 18:48:49 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	init_pipex(int a)
{
	t_pipe	pipex;
	int		i;

	pipex.procecess_num = a;
	pipex.pipes = (int **)malloc((pipex.procecess_num + 1) * sizeof(int *));
	pipex.exe = (t_exe *)malloc((pipex.procecess_num + 1) * sizeof(t_exe));
	pipex.pid = (int *)malloc((pipex.procecess_num) * sizeof(int));
	pipex.stdin_file = NULL;
	pipex.stdout_file = NULL;
	pipex.exe[0].c_split = NULL;
	pipex.append = 0;
	pipex.heredoc = 0;
	i = -1;
	while (++i < pipex.procecess_num + 1)
		pipex.pipes[i] = (int *)malloc((2) * sizeof(int));
	i = -1;
	while (++i < pipex.procecess_num + 1)
		if (pipe(pipex.pipes[i]) == -1)
			exit (0);
	return (pipex);
}

int	pipex_4(t_pipe *pipex, int po)
{
	if (ft_arraybilen(pipex->com) > po && ft_strcmp(pipex->com[po]
			, "<") && ft_strcmp(pipex->com[po], ">")
		&& ft_strcmp(pipex->com[po], "<<")
		&& ft_strcmp(pipex->com[po], ">>"))
		pipex->tomas = ft_strjoin_space(pipex->tomas, pipex->com[po]);
	else
		return (po);
	while (ft_arraybilen(pipex->com) > po + 1 && ft_strcmp(pipex->com[po + 1]
			, "<") && ft_strcmp(pipex->com[po + 1], ">")
		&& ft_strcmp(pipex->com[po + 1], "<<")
		&& ft_strcmp(pipex->com[po + 1], ">>"))
	{
		pipex->tomas = ft_strjoin_space(pipex->tomas, pipex->com[po + 1]);
		po++;
	}
	po++;
	return (po);
}
