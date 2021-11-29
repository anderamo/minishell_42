/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 18:19:13 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/29 14:22:34 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(char *src)
{
	size_t	size;
	char	*dst;

	size = ft_strlen((char *)src) + 1;
	dst = malloc(size);
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, src, size);
	free(src);
	return (dst);
}
