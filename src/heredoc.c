/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:51 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/26 17:56:22 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
