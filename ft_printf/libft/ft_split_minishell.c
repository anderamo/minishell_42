/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:56:43 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/22 19:01:56 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_create_fill_array(char *s, char c, char **split, ssize_t array_count)
{
	char	*string;
	size_t	string_size;
	ssize_t	array_row;
	size_t	i;

	i = 0;
	string_size = 0;
	array_row = 0;
	while (array_count > array_row)
	{
		while (s[i] != c && s[i])
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				c = s[i];
				i++;
				string_size++;
				while (s[i] != '\0' && s[i] != c)
				{
					i++;
					string_size++;
				}
				c = ' ';
			}
			if (s[i] == '<' || s[i] == '>')
			{
				if (string_size != 0)
				{
					break ;
				}
				c = s[i];
				string_size++;
				i++;
				if (ft_strlen(s) > i && s[i] == c)
				{
					string_size++;
					i++;
				}
				c = ' ';
				break ;
			}
			i++;
			string_size++;
		}
		if (string_size > 0)
		{
			string = ft_calloc(string_size + 1, sizeof(char ));
			ft_memcpy(string, s + i - string_size, string_size);
			split[array_row] = string;
			array_row++;
			string_size = 0;
			if (s[i] != ' ')
				i--;
		}
			i++;
	}
}

static ssize_t	ft_get_array_row(char *s, size_t i, ssize_t count, int quote)
{
	char	c;

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
			if (s[i] == '<' || s[i] == '>')
			{
				if (ft_strlen(s) > i - 1 && s[i - 1] != ' ' && s[i - 1] != '>' && s[i - 1] != '<')
					count++;
				c = s[i];
				if (ft_strlen(s) > i + 1 && (s[i + 1] == c))
					i++;
				c = ' ';
				if (ft_strlen(s) > i + 1 && s[i + 1] != ' ')
					count++;
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
	ssize_t		array_row;
	char		**array;

	if (!s)
		return (NULL);
	array_row = ft_get_array_row(s, 0, 0 ,0);
	if (array_row == -1)
	{
		write(1, "Error the quote are not close\n", 31);
		return (NULL);
	}
	//printf("s -----------> %s\n", s);
	//printf("array_row ---> %zu\n", array_row);
	array = malloc((array_row + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	ft_create_fill_array(s, ' ', array, array_row);
	array[array_row] = NULL;
	return (array);
}

/*
int	main(int argc, char **argv)
{
	char **split;

	if (argc > 1)
		split = ft_split_minishell(argv[1]);
	if (!split)
		return (1);
	int i = 0;
	while (split[i])
	{
		printf("split%d ---------> %s\n", i, split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}
*/

