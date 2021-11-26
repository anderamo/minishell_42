/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:25:18 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/26 16:39:00 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	init_pipex(int a, int i)
{
	t_pipe	pipex;

	pipex.procecess_num = a;
	pipex.pipes = (int **)malloc((pipex.procecess_num + 1) * sizeof(int *));
	pipex.exe = (t_exe *)malloc((pipex.procecess_num + 1) * sizeof(t_exe));
	pipex.pid = (int *)malloc((pipex.procecess_num) * sizeof(int));
	pipex.exe[0].c_split = NULL;
	while (++i < pipex.procecess_num + 1)
	{
		pipex.pipes[i] = (int *)malloc((2) * sizeof(int));
		pipex.exe[i].stdin_file = NULL;
		pipex.exe[i].stdout_file = NULL;
		pipex.exe[i].append = 0;
		pipex.exe[i].heredoc = 0;
	}
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
