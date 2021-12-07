/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:56:43 by aamorin-          #+#    #+#             */
/*   Updated: 2021/12/07 14:06:40 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	string_redirreccion(int *i, int *string_size, char *s)
{
	char	c;

	if (s[*i] == '<' || s[*i] == '>')
	{
		if (*string_size != 0)
			return (-1);
		c = s[*i];
		*string_size = *string_size + 1;
		*i = *i + 1;
		if ((int)ft_strlen(s) > *i && s[*i] == c)
		{
			*string_size = *string_size + 1;
			*i = *i + 1;
		}
		c = ' ';
		return (-1);
	}
	*i = *i + 1;
	*string_size = *string_size + 1;
	return (0);
}

static void	string_comma(int *i, int *string_size, char *s)
{
	char	c;

	if (s[*i] == '\'' || s[*i] == '\"')
	{
		c = s[*i];
		*i = *i + 1;
		*string_size = *string_size + 1;
		while (s[*i] != '\0' && s[*i] != c)
		{
			*i = *i + 1;
			*string_size = *string_size + 1;
		}
		c = ' ';
	}
}

static void	ft_create_fill_array(char *s, size_t string_size,
		char **split, ssize_t array_count)
{
	char	*string;
	ssize_t	array_row;
	size_t	i;

	i = 0;
	array_row = 0;
	while (array_count > array_row)
	{
		while (s[i] != ' ' && s[i])
		{
			string_comma((int *)&i, (int *)&string_size, s);
			if (string_redirreccion((int *)&i, (int *)&string_size, s) == -1)
				break ;
		}
		if (string_size > 0)
		{
			string = ft_calloc(string_size + 1, sizeof(char ));
			ft_memcpy(string, s + i - string_size, string_size);
			split[array_row++] = string;
			string_size = 0;
			if (s[i] != ' ')
				i--;
		}
			i++;
	}
}

static ssize_t	ft_get_array_row(char *s, size_t i,
		ssize_t count, int quote)
{
	char	c;
	int		comma;

	c = ' ';
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
		{
			comma = count_comma((int *)&i, (int *)&quote, s);
			if (comma == -1)
				break ;
			if (comma == -2)
				continue ;
			count_redireccion((int *)&i, (int *)&count, s);
			i++;
		}
		count++;
	}
	if (quote % 2 != 0 && quote != 0)
		return (-1);
	return (count);
}

char	**ft_split_minishell(char *s)
{
	ssize_t		array_row;
	char		**array;

	if (!s)
		return (NULL);
	array_row = ft_get_array_row(s, 0, 0, 0);
	if (array_row == -1)
	{
		write(1, "Error the quote are not close\n", 31);
		return (NULL);
	}
	array = malloc((array_row + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	ft_create_fill_array(s, 0, array, array_row);
	array[array_row] = NULL;
	return (array);
}
