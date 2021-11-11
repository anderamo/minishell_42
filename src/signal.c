/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:07:32 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/11 16:22:58 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last_error(void)
{
	printf("bash: %d: command not found\n", g_mini.last_error);
	g_mini.last_error = 127;
	return (1);
}

void	ft_action(int sig)
{
	printf("\n");
	write_pwd();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (sig == 0)
		return ;
}

void	signal_proc(void)
{
	signal(SIGINT, ft_action);
	signal(SIGQUIT, SIG_IGN);
}
