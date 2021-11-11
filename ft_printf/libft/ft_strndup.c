/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:57:58 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/11 15:59:26 by migarcia         ###   ########.fr       */
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
