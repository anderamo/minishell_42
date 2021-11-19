/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:37:48 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/18 20:59:36 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_get_array_row(char const *s, size_t i, size_t count, size_t size)
{
	char	c;
	int		quote;

	quote = 0;
	c = ' ';
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				c = s[i];
				i++;
				quote++;
				while (s[i] != '\0' && s[i] != c)
					i++;
				if (s[i] == '\0')
					break ;
				c = ' ';
				quote++;
				i++;
				continue ;
			}
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
	size_t		array_row;
	char		**array;

	if (!s)
		return (NULL);
	array_row = ft_get_array_row(s, 0, 0 ,0);
	if (array_row == -1)
	{
		printf("Error the quote are not close");
		return (NULL);
	}
	printf("s -----------> %s\n", s);
	printf("array_row ---> %zu\n", array_row);
	/*
	array = malloc((array_row + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	ft_create_fill_array(s, c, array, array_row);
	array[array_row] = NULL;
	*/
	return (array);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		ft_split_minishell(argv[1]);
	return (1);
}


/*
static size_t	ft_get_array_row(char const *s, size_t i, size_t count, size_t size)
{
	char	c;
	int		quote;

	quote = 0;
	c = ' ';
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (size != 0)
				count++;
			size = 0;
		}
		else if (s[i] == '\"' || s[i] == '\'')
		{
			quote++;
			if (quote % 2 == 0)
				c = ' ';
			else
				c = s[i];
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
}
*/
