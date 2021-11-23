/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:07:32 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/23 16:53:29 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	ft_last_error(void)
{
	printf("bash: %d: command not found\n", g_mini.last_error);
	g_mini.last_error = 127;
	return (1);
}

void	ft_action(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_mini.pid == 0)
			rl_redisplay();
	}
	if (sig == SIGQUIT && g_mini.pid != 0)
	{
		printf("Quit: 3\n");
		kill(g_mini.pid, SIGQUIT);
		g_mini.pid = 0;
	}
	else if (sig == SIGQUIT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_mini.pid = 0;
}

void	signal_proc(void)
{
	signal(SIGINT, ft_action);
	signal(SIGQUIT, ft_action);
}
