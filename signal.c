/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:07:32 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/05 15:13:15 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_action(int sig)
{
	(void)sig;
	printf("\n");
	write_pwd(g_mini.enva);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_proc()
{
	signal(SIGINT, ft_action);
	signal(SIGQUIT, SIG_IGN);
}
