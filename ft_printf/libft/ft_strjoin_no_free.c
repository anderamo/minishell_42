/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_no_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 10:57:14 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/24 18:12:22 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_no_free(char const *s1, char const *s2)
{
	char	*array;
	size_t	s1_size;
	size_t	s2_size;
	size_t	total_size;
	size_t	i;

	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (0);
	s1_size = ft_strlen((char *)s1);
	s2_size = ft_strlen((char *)s2);
	total_size = s1_size + s2_size;
	array = malloc((total_size) + 1);
	if (!array)
		return (0);
	ft_memmove(array, s1, s1_size);
	array[s1_size] = ' ';
	ft_memmove(array + s1_size, s2, s2_size);
	array[total_size] = '\0';
	return (array);
}
