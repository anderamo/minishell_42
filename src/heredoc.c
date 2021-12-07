/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:51 by aamorin-          #+#    #+#             */
/*   Updated: 2021/12/06 20:57:06 by aamorin-         ###   ########.fr       */
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
