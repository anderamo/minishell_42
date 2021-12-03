/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:51:04 by migarcia          #+#    #+#             */
/*   Updated: 2021/12/02 19:30:10 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(const char *str, int pos)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[pos] && !(ft_isspace(str[pos])) && str[pos] != '$'
		&& str[pos] != '/' && str[pos] != '\"' && str[pos] != '\'')
	{
		pos++;
		i++;
	}
	return (i);
}

char	*find_env(char *src, int pos)
{
	int		len;
	char	*temp;
	char	*dest;
	int		j;

	len = env_len(src, pos);
	temp = malloc(sizeof(char) * (len + 1));
	j = 0;
	while (len > j)
	{
		temp[j] = src[pos];
		j++;
		pos++;
	}
	temp[len] = '\0';
	dest = ft_getenv(temp);
	free(temp);
	return (dest);
}

int	ft_copy_quote(char **commands, t_cmd *cmd, size_t i, int j)
{
	if (commands[i][j] == '\'' || commands[i][j] == '\"')
	{
		if (commands[i][j] == '\"')
		{
			j++;
			while (commands[i][j] && commands[i][j] != '\"')
			{
				if (commands[i][j] == '$')
					j += ft_dollar(cmd, commands[i], '\"', j + 1);
				else if (commands[i][j] != '\"')
					write(1, &commands[i][j], 1);
				j++;
			}
		}
		if (commands[i][j] == '\'')
		{
			while (commands[i][++j] && commands[i][j] != '\'')
				write(1, &commands[i][j], 1);
		}
	}
	else if (commands[i][j] == '$')
		j += ft_dollar(cmd, commands[i], '\"', j + 1);
	else
		write(1, &commands[i][j++], 1);
	return (j);
}
