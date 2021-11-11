/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:51 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/11 17:18:15 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(char *del)
{
	char	*line;
	int		fd;

	fd = open("heredoc_tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		line = readline("\033[36mheredoc> \033[0m");
		if (!ft_strcmp(line, del))
			break ;
		write (fd, line, ft_strlen(line));
		write (fd, "\n", 1);
	}
}
