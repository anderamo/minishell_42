/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:54:45 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/08 09:23:15 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(char **env)
{
	int		i;

	if (!env || !(*env))
		return (0);
	g_mini.env = (char **)malloc(sizeof(char *) * (ft_array_size(env) + 2));
	if (!(g_mini.env))
		return (0);
	i = 0;
	while (env[i])
	{
		g_mini.env[i] = ft_strdup(env[i]);
		if (!g_mini.env[i])
		{
			ft_frlloc_n(g_mini.env, i);
			return (0);
		}
		i++;
	}
	g_mini.env[i] = NULL;
	return (1);
}