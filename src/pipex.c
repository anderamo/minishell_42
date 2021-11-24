/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:34:40 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/24 11:01:16 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex_3_1(t_pipe *pipex, int index)
{
	if (ft_arraybilen(pipex->com) > index
		&& !ft_strcmp(pipex->com[index], "<<"))
	{
		if (ft_arraybilen(pipex->com) > index + 1)
		{
			ft_heredoc(pipex->com[++index]);
			pipex->heredoc = 1;
			g_mini.pid = 0;
		}
		else
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			g_mini.last_error = 258;
			ft_frlloc(pipex->com);
			return (-1);
		}
		index++;
	}
	return (index);
}

int	pipex_3(t_pipe *pipex, int index)
{
	index = pipex_3_1(pipex, index);
	if (index == -1)
		return (-1);
	if (ft_arraybilen(pipex->com) > index
		&& !ft_strcmp(pipex->com[index], "<"))
	{
		if (ft_arraybilen(pipex->com) > index + 1)
		{
			if (pipex->stdin_file != NULL)
				free(pipex->stdin_file);
			pipex->stdin_file = ft_strdup(pipex->com[++index]);
		}
		else
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			g_mini.last_error = 258;
			ft_frlloc(pipex->com);
			return (-1);
		}
		index++;
	}
	return (index);
}

int	pipex_2_1(t_pipe *pipex, int index)
{
	if (ft_arraybilen(pipex->com) > index && !ft_strcmp(pipex->com[index], ">"))
	{
		if (ft_arraybilen(pipex->com) > index + 1)
		{
			if (pipex->stdout_file != NULL)
				free(pipex->stdout_file);
			pipex->stdout_file = ft_strdup(pipex->com[index + 1]);
			pipex->append = 0;
			index += 2;
		}
		else
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			g_mini.last_error = 258;
			ft_frlloc(pipex->com);
			return (-1);
		}
	}
	return (index);
}

int	pipex_2(t_pipe *pipex, int i)
{
	i = pipex_2_1(pipex, i);
	if (i == -1)
		return (-1);
	if (ft_arraybilen(pipex->com) > i && !ft_strcmp(pipex->com[i], ">>"))
	{
		if (ft_arraybilen(pipex->com) > i && ft_strcmp(pipex->com[i + 1], ">")
			&& ft_strcmp(pipex->com[i + 1], ">>")
			&& ft_strcmp(pipex->com[i + 1], "<")
			&& ft_strcmp(pipex->com[i + 1], "<<"))
		{
			if (pipex->stdout_file != NULL)
				free(pipex->stdout_file);
			pipex->stdout_file = ft_strdup(pipex->com[i + 1]);
			pipex->append = 1;
			i += 2;
		}
		else
		{
			printf("bash: syntax error near unexpected token `>'\n");
			g_mini.last_error = 258;
			ft_frlloc(pipex->com);
			return (-1);
		}
	}
	return (i);
}

void	pipex(char **argv, int count, int a, int index)
{
	t_pipe	pipex;

	pipex = init_pipex(count);
	while (argv[++a])
	{
		pipex.com = ft_split_minishell(argv[a]);
		if (!pipex.com)
			return ;
		index = 0;
		pipex.tomas = NULL;
		while (ft_arraybilen(pipex.com) > index && pipex.com[index])
		{
			index = pipex_2(&pipex, index);
			if (index == -1)
				return ;
			index = pipex_3(&pipex, index);
			if (index == -1)
				return ;
			index = pipex_4(&pipex, index);
		}
		pipex.exe[a].c_split = ft_split_minishell(pipex.tomas);
		free_pipex(&pipex);
	}
	if (pipex.exe[0].c_split != NULL || pipex.heredoc == 1)
		create_processes(pipex);
}
