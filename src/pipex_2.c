/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:25:18 by aamorin-          #+#    #+#             */
/*   Updated: 2021/12/07 12:48:27 by aamorin-         ###   ########.fr       */
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
	pipex.stdin_file = NULL;
	pipex.stdout_file = NULL;
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

/*
int	errors_expr(t_pipe pipex, int i, int *c, int j)
{
	if (!ft_strcmp(pipex.exe[i].c_split[j], "$?") && j % 2 != 0)
	{
		if (g_mini.last_error == 0 && *c == 1)
			g_mini.last_error = 1;
		else if (g_mini.last_error != 0 && *c == 1)
			g_mini.last_error = 0;
		*c = *c + 1;
	}
	else if (!ft_isnumber(pipex.exe[i].c_split[j]) && j % 2 != 0)
	{
		g_mini.last_error = 2;
		return (-1);
	}
	*/
	//if (j % 2 == 0 && !ft_strchr("+-*/%=", pipex.exe[i].c_split[j][0]))
	/*
	{
		g_mini.last_error = 2;
		return (-1);
	}
	return (1);
}

void	check_expr(t_pipe pipex, int i, int j, int c)
{
	if (pipex.exe[i].c_split && !ft_strcmp(pipex.exe[i].c_split[0], "expr"))
	{
		while (i < pipex.procecess_num)
		{
			j = 1;
			while ((int)ft_array_size(pipex.exe[i].c_split) > j)
			{
				if (!ft_strcmp(pipex.exe[i].c_split[0], "expr"))
				{
					if (errors_expr(pipex, i, &c, j) == -1)
						break ;
				}
				j++;
			}
			if (j % 2 != 0)
				g_mini.last_error = 2;
			i++;
		}
	}
}

void	check_errors(t_pipe pipex, int i, int j, int c)
{
	int	fd;

	if (pipex.exe[i].c_split && !ft_strcmp(pipex.exe[i].c_split[0], "expr"))
		check_expr(pipex, i, j, c);
	else
	{
		while (i < pipex.procecess_num)
		{
			j = 1;
			while ((int)ft_array_size(pipex.exe[i].c_split) > j
				&& ft_strcmp(pipex.exe[i].c_split[0], "echo"))
			{
				if (!ft_strncmp(pipex.exe[i].c_split[j], "-", 1))
					j++;
				else
				{
					fd = open(pipex.exe[i].c_split[j], O_RDONLY);
					if (fd == -1)
						g_mini.last_error = 1;
					j++;
				}
			}
		i++;
		}
	}
}
*/
