/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:07:32 by migarcia          #+#    #+#             */
/*   Updated: 2021/12/01 18:23:39 by migarcia         ###   ########.fr       */
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
	(void)sig;
	printf("\r");
	write(1, "\n", 1);
	if (g_mini.pid == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_mini.last_error = 1;
	}
	if (g_mini.stop == 1)
	{
		close(g_mini.fd);
		g_mini.last_error = 1;
	}
	else
		g_mini.last_error = 130;
}

void	ft_quit_action(int sig)
{
	if (sig == SIGQUIT && g_mini.pid != 0)
	{
		printf("Quit: 3\n");
		kill(g_mini.pid, SIGQUIT);
		g_mini.pid = 0;
		g_mini.last_error = 131;
	}
	g_mini.pid = 0;
}

void	signal_proc(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_int_action);
	signal(SIGQUIT, ft_quit_action);
}
