/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:34:40 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/17 19:24:56 by aamorin-         ###   ########.fr       */
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
	if (!ft_strcmp(pipex->com[index], ">"))
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

int	pipex_2(t_pipe *pipex, int index)
{
	index = pipex_2_1(pipex, index);
	if (index == -1)
		return (-1);
	if (ft_arraybilen(pipex->com) > index
		&& !ft_strcmp(pipex->com[index], ">>"))
	{
		if (pipex->stdout_file != NULL)
			free(pipex->stdout_file);
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

	pipex = init_pipex(count);
	while (argv[++a])
	{
		pipex.com = ft_split(argv[a], ' ');
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
		pipex.exe[a].c_split = ft_split(pipex.tomas, ' ');
		free_pipex(&pipex);
	}
	if (pipex.exe[0].c_split != NULL)
		create_processes(pipex);
}
