/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:02:38 by aamorin-          #+#    #+#             */
/*   Updated: 2021/08/30 19:02:21 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_create_fill_array(char *s, char c,
		char **array, size_t array_size)
{
	char	*string;
	size_t	string_size;
	size_t	array_row;
	size_t	i;

	i = 0;
	string_size = 0;
	array_row = 0;
	while (array_size > array_row)
	{
		while (s[i] != c && s[i])
		{
			i++;
			string_size++;
		}
		if (string_size > 0)
		{
			string = ft_calloc(string_size + 1, sizeof(char));
			ft_memcpy(string, s + i - string_size, string_size);
			array[array_row] = string;
			array_row++;
			string_size = 0;
		}
		i++;
	}
}

static size_t	ft_get_array_row(char *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	size;

	i = 0;
	count = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] == c)
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

char	**ft_split(char *s, char c)
{
	size_t		array_row;
	char		**array;

	if (!s)
		return (NULL);
	array_row = ft_get_array_row(s, c);
	array = malloc((array_row + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	ft_create_fill_array(s, c, array, array_row);
	array[array_row] = NULL;
	return (array);
}
