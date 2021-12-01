/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:51:04 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/30 20:04:37 by migarcia         ###   ########.fr       */
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
	char	c;

	if (commands[i][j] == '\'' || commands[i][j] == '\"')
	{
		c = commands[i][j];
		j++;
		while ((int)ft_strlen(commands[i]) > j)
		{
			if (commands[i][j] == '$')
				j += ft_dollar(cmd, commands[i], c, j + 1);
			else if (commands[i][j] != c)
				write(1, &commands[i][j], 1);
			if ((int)ft_strlen(commands[i]) > j && commands[i][j] == c)
				j++;
			j++;
		}
	}
	else if (commands[i][j] == '$')
		j += ft_dollar(cmd, commands[i], '\"', j + 1) + 1;
	else
		write(1, &commands[i][j++], 1);
	return (j);
}
