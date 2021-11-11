/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:34:40 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/11 16:02:25 by aamorin-         ###   ########.fr       */
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
	i = 0;
	while (i < pipex.procecess_num + 1)
	{
		if (pipe(pipex.pipes[i]) == -1)
			exit (0);
		i++;
	}
	return (pipex);
}

int	pipex_4(t_pipe *pipex, int po, int i, int a)
{
	while (ft_arraybilen(pipex->com) > po + 1 && ft_strcmp(pipex->com[po + 1]
			, "<") && ft_strcmp(pipex->com[po + 1], ">")
		&& ft_strcmp(pipex->com[po + 1], "<<")
		&& ft_strcmp(pipex->com[po + 1], ">>"))
	{
		pipex->com[i] = ft_strjoin_space(pipex->com[i], pipex->com[po + 1]);
		po++;
	}
	pipex->exe[a].c_split = ft_split(pipex->com[i], ' ');
	po++;
	if (ft_arraybilen(pipex->com) > po + 1 && !ft_strcmp(pipex->com[po], "<"))
	{
		pipex->stdin_file = ft_strdup(pipex->com[po + 1]);
		po += 2;
	}
	else if (ft_arraybilen(pipex->com) > po + 1
		&& !ft_strcmp(pipex->com[po], ">"))
	{
		pipex->stdout_file = ft_strdup(pipex->com[po + 1]);
		pipex->append = 0;
		po += 2;
	}
	else
		po++;
	return (po);
}

int	pipex_3(t_pipe *pipex, int index)
{
	if (ft_arraybilen(pipex->com) > index
		&& !ft_strcmp(pipex->com[index], "<<"))
	{
		if (ft_arraybilen(pipex->com) > index + 1)
		{
			ft_heredoc(pipex->com[++index]);
			pipex->heredoc = 1;
		}
		else
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			g_mini.last_error = 258;
			return (-1);
		}
		index++;
	}
	else if (ft_arraybilen(pipex->com) > index
		&& !ft_strcmp(pipex->com[index], "<"))
	{
		pipex->stdin_file = ft_strdup(pipex->com[index + 1]);
		index += 2;
	}
	return (index);
}

int	pipex_2(t_pipe *pipex, int index)
{
	if (!ft_strcmp(pipex->com[index], ">"))
	{
		pipex->stdout_file = ft_strdup(pipex->com[index + 1]);
		pipex->append = 0;
		index += 2;
	}
	else if (ft_arraybilen(pipex->com) > index
		&& !ft_strcmp(pipex->com[index], ">>"))
	{
		pipex->stdout_file = ft_strdup(pipex->com[index + 1]);
		pipex->append = 1;
		index += 2;
	}
	return (index);
}

void	pipex(char **argv, int count, int a)
{
	t_pipe	pipex;
	int		index;

	add_history(g_mini.line);
	pipex = init_pipex(count);
	while (argv[++a])
	{
		pipex.com = ft_split(argv[a], ' ');
		index = 0;
		while (ft_arraybilen(pipex.com) > index && pipex.com[index])
		{
			index = pipex_2(&pipex, index);
			index = pipex_3(&pipex, index);
			if (index == -1)
				return ;
			index = pipex_4(&pipex, index, index, a);
		}
		ft_frlloc(pipex.com);
		if (!ft_strcmp(pipex.exe[a].c_split[0], "ls")
			|| !ft_strcmp(pipex.exe[a].c_split[0], "cat"))
			if (!check_if_exits(pipex, a))
				return ;
	}
	if (pipex.exe[0].c_split != NULL)
		create_processes(pipex);
}
