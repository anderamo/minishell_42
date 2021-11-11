/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:54:38 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/11 16:12:02 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_array_size(char **arr)
{
	int		size;

	if (!arr || !(*arr))
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}

char	**ft_frlloc(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	ft_frlloc_n(char **tab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
}

int	ft_arraybilen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**ft_frlloc_int(int **tab, int size)
{
	int	i;

	i = 0;
	while (size > i)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}
