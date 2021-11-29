/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:02:38 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/29 09:29:10 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isquote(char const *s, int i)
{
	int	index;
	int	quote;

	index = 0;
	quote = 0;
	while (index < i)
	{
		if (s[index] == '\"')
			quote++;
		index++;
	}
	if (quote % 2 != 0 && quote != 0)
	{
		return (-1);
	}
	return (1);
}

static void	ft_create_fill_array(char *s, int i,
								char **array, size_t array_size)
{
	char	*string;
	size_t	string_size;
	size_t	array_row;

	array_row = 0;
	while (array_size > array_row && i++)
	{
		string_size = 0;
		while (s[i] && s[i] != '|')
		{
			i++;
			if ((int)ft_strlen(s) > i && s[i] == '|' && isquote(s, i) == -1)
			{
					i++;
					string_size++;
			}
			string_size++;
		}
		if (string_size > 0)
		{
			string = ft_calloc(string_size + 1, sizeof(char ));
			ft_memcpy(string, s + i - string_size, string_size);
			array[array_row++] = string;
		}
	}
}

static size_t	ft_get_array_row(char const *s, size_t i,
	size_t count, size_t	size)
{
	while (s[i])
	{
		if (s[i] == '|' && isquote(s, i) == 1)
		{
			if (size != 0)
				count++;
			size = 0;
		}
		else
			size++;
		i++;
	}
	if (size != 0)
		size = 1;
	else
		size = 0;
	return (count + size);
}

char	**ft_split_pipe(char const *s)
{
	size_t		array_row;
	char		**array;

	if (!s)
		return (NULL);
	array_row = ft_get_array_row(s, 0, 0, 0);
	array = malloc((array_row + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	ft_create_fill_array((char *)s, -1, array, array_row);
	array[array_row] = NULL;
	return (array);
}
