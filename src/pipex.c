/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:34:40 by aamorin-          #+#    #+#             */
/*   Updated: 2021/12/02 18:24:39 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex_3_1(t_pipe *pipex, int index, int a)
{
	if (ft_arraybilen(pipex->com) > index
		&& !ft_strcmp(pipex->com[index], "<<"))
	{
		if (ft_arraybilen(pipex->com) > index + 1)
		{
			ft_heredoc(pipex->com[++index]);
			pipex->exe[a].heredoc = 1;
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

int	pipex_3(t_pipe *pipex, int index, int a)
{
	index = pipex_3_1(pipex, index, a);
	if (index == -1)
		return (-1);
	if (ft_arraybilen(pipex->com) > index
		&& !ft_strcmp(pipex->com[index], "<"))
	{
		if (ft_arraybilen(pipex->com) > index + 1)
		{
			if (pipex->exe[a].stdin_file != NULL)
				free(pipex->exe[a].stdin_file);
			pipex->exe[a].stdin_file = ft_strdup(pipex->com[++index]);
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

int	pipex_2_1(t_pipe *pipex, int index, int a)
{
	if (ft_arraybilen(pipex->com) > index && !ft_strcmp(pipex->com[index], ">"))
	{
		if (ft_arraybilen(pipex->com) > index + 1)
		{
			if (pipex->exe[a].stdout_file != NULL)
				free(pipex->exe[a].stdout_file);
			pipex->exe[a].stdout_file = ft_strdup(pipex->com[index + 1]);
			pipex->exe[a].append = 0;
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

int	pipex_2(t_pipe *pipex, int i, int a)
{
	i = pipex_2_1(pipex, i, a);
	if (i == -1)
		return (-1);
	if (ft_arraybilen(pipex->com) > i && !ft_strcmp(pipex->com[i], ">>"))
	{
		if (ft_arraybilen(pipex->com) > i && ft_strcmp(pipex->com[i + 1], ">")
			&& ft_strcmp(pipex->com[i + 1], ">>")
			&& ft_strcmp(pipex->com[i + 1], "<")
			&& ft_strcmp(pipex->com[i + 1], "<<"))
		{
			if (pipex->exe[a].stdout_file != NULL)
				free(pipex->exe[a].stdout_file);
			pipex->exe[a].stdout_file = ft_strdup(pipex->com[i + 1]);
			pipex->exe[a].append = 1;
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

void	pipex(char **argv, t_pipe pipex, int a, int index)
{
	while (argv[++a])
	{
		pipex.com = ft_split_minishell(argv[a]);
		if (!pipex.com)
			return ;
		if (!builtins_no_pipe(argv[a], pipex.com))
		{
			index = 0;
			pipex.tomas = NULL;
			while (ft_arraybilen(pipex.com) > index && pipex.com[index])
			{
				index = pipex_2(&pipex, index, a);
				if (index == -1)
					return ;
				index = pipex_3(&pipex, index, a);
				if (index == -1)
					return ;
				index = pipex_4(&pipex, index);
			}
			pipex.exe[a].c_split = ft_split_minishell(pipex.tomas);
			free_pipex(&pipex);
		}
	}
	if (pipex.exe[0].c_split != NULL || pipex.exe[0].heredoc == 1)
		create_processes(pipex, -1);
}
