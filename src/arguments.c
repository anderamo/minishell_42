/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:51:04 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/23 19:13:30 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && !(ft_isspace(str[i])) && str[i] != '$'
		&& str[i] != '/' && str[i] != '\"' && str[i] != '\'')
	i++;
	return (i);
}

char	*find_env(char *src, int *i)
{
	int		len;
	char	*temp;
	char	*dest;

	len = env_len(src);
	(*i) += len + 1;
	temp = ft_strndup(src, len);
	dest = ft_getenv(temp);
	free(temp);
	return (dest);
}

void	expand_env(char *dest, char *src, int *i)
{
	char	*env;

	if (src[*i + 1] == '$')
		(*i) += 2;
	else if (src[*i + 1] && !(ft_isspace(src[*i + 1])))
	{
		env = find_env(&src[*i + 1], i);
		if (env)
			ft_strncat(dest, env, ft_strlen(env));
	}
	else
		ft_strncat(dest, &src[(*i)++], 1);
}

int	copy_quote(char *dest, char *src, int i, char *error)
{
	char	c;

	c = src[i++];
	while (src[i] && src[i] != c)
	{
		if (c == '\"' && src[i] == '$')
		{
			if (src[i + 1] == '?')
				ft_strncat(dest, error, ft_strlen(error));
			expand_env(dest, src, &i);
		}
		else
		{
			ft_strncat(dest, &src[i++], 1);
		}
	}
	if (src[i])
		i++;
	return (i);
}
