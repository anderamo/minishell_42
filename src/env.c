/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:54:45 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/11 17:21:43 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_len_to_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_getenv(char *name)
{
	int		i;
	int		j;
	size_t	len;

	if (!name)
		return (NULL);
	len = ft_strlen(name);
	i = 1;
	while (g_mini.env[i])
	{
		if (ft_strlen(name) >= ft_len_to_char(g_mini.env[i], '=')
			&& ft_strncmp(g_mini.env[i], name, len) == 0)
		{
			j = 0;
			while (g_mini.env[i][j] && g_mini.env[i][j] != '=')
				j++;
			return (&g_mini.env[i][++j]);
		}
		i++;
	}
	return (NULL);
}

int	init_env(char **env)
{
	int		i;

	if (!env || !(*env))
		return (0);
	g_mini.env = (char **)malloc(sizeof(char *) * (ft_array_size(env) + 2));
	g_mini.last_error = 0;
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
	signal_proc();
	return (1);
}
