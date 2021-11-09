/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:54:38 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/08 09:20:59 by aamorin-         ###   ########.fr       */
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
	int i;

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
