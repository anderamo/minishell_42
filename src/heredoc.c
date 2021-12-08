/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:51 by aamorin-          #+#    #+#             */
/*   Updated: 2021/12/08 08:49:18 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waitpid_last_error(t_pipe pipex, int i)
{
	int	status;

	waitpid(pipex.pid[i], &status, 0);
	if (WIFEXITED(status) && pipex.exe[i].c_split
		&& (ft_strcmp(pipex.exe[i].c_split[0], "echo"))
		&& (ft_strcmp(pipex.exe[i].c_split[0], "cd"))
		&& (ft_strcmp(pipex.exe[i].c_split[0], "pwd"))
		&& (ft_strcmp(pipex.exe[i].c_split[0], "export"))
		&& (ft_strcmp(pipex.exe[i].c_split[0], "unset"))
		&& (ft_strcmp(pipex.exe[i].c_split[0], "env"))
		&& (ft_strcmp(pipex.exe[i].c_split[0], "exit")))
			g_mini.last_error = WEXITSTATUS(status);
}

int	isquote(char const *s, int i)
{
	int	index;
	int	quote1;
	int	quote2;

	index = 0;
	quote1 = 0;
	quote2 = 0;
	while (index < i)
	{
		if (s[index] == '\"')
			quote1++;
		if (s[index] == '\'')
			quote2++;
		index++;
	}
	if ((quote1 % 2 != 0 && quote1 != 0) || (quote2 % 2 != 0 && quote2 != 0))
	{
		printf("ERROR: Wrong export format\n");
		g_mini.last_error = 1;
		return (-1);
	}
	return (1);
}

int	check_next_dollar(char **commands, size_t i, int j)
{
	char	*dst;

	if (ft_array_size(commands) > i && commands[i][j] == '$')
	{
		if (commands[i][j + 1] != '?')
		{
			dst = find_env(commands[i], j + 1);
			if (dst)
				return (1);
			else
				return (0);
		}
	}
	return (1);
}

void	ft_heredoc(char *del)
{
	char	*line;

	g_mini.fd = open("heredoc_tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	g_mini.pid = 1;
	line = readline("> ");
	while (line && ft_strcmp(line, del))
	{
		if (g_mini.stop)
			break ;
		write (g_mini.fd, line, ft_strlen(line));
		write (g_mini.fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	g_mini.pid = 0;
	close(g_mini.fd);
}
