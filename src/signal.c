/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:07:32 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/24 10:45:43 by aamorin-         ###   ########.fr       */
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

void	ft_int_action(int sig)
{
	if (sig == SIGINT && g_mini.pid == 0)
	{
		printf("\033[2K\r");
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
	else if (sig == SIGINT)
	{
		printf("\r");
		write(1, "\n", 1);
	}
}

void	ft_quit_action(int sig)
{
	if (sig == SIGQUIT && g_mini.pid != 0)
	{
		printf("Quit: 3\n");
		kill(g_mini.pid, SIGQUIT);
		g_mini.pid = 0;
	}
	else if (sig == SIGQUIT)
	{
		printf("\033[2K");
		rl_on_new_line();
		rl_redisplay();
	}
	g_mini.pid = 0;
}

void	signal_proc(void)
{
	signal(SIGINT, ft_int_action);
	signal(SIGQUIT, ft_quit_action);
}
