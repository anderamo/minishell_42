/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:57:58 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/11 17:15:59 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int n)
{
	int		len;
	char	*d;

	len = ft_strlen(s) + 1;
	if (len > n)
		len = n;
	d = malloc(sizeof(char *) * len);
	if (!d)
		return (NULL);
	return (ft_memcpy(d, s, len));
}
