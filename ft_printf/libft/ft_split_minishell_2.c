/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:56:43 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/24 13:29:39 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	count_redireccion(int *i, int *count, char *s)
{
	char	c;

	if ((int)ft_strlen(s) > *i && (s[*i] == '<' || s[*i] == '>'))
	{
		if ((int)ft_strlen(s) > *i - 1 && s[*i - 1] != ' '
			&& s[*i - 1] != '>' && s[*i - 1] != '<' && *i != 0)
			*count = *count + 1;
		c = s[*i];
		if ((int)ft_strlen(s) > *i + 1 && (s[*i + 1] == c))
			*i = *i + 1;
		c = ' ';
		if ((int)ft_strlen(s) > *i + 1 && s[*i + 1] != ' ')
			*count = *count + 1;
	}
}

int	count_comma(int *i, int *quote, char *s)
{
	char	c;

	if (s[*i] == '\'' || s[*i] == '\"')
	{
		c = s[*i];
		*i = *i + 1;
		*quote = *quote + 1;
		while (s[*i] != '\0' && s[*i] != c)
			*i = *i + 1;
		if (s[*i] == '\0')
			return (-1);
		c = ' ';
		*quote = *quote + 1;
		*i = *i + 1;
		return (-2);
	}
	return (0);
}
