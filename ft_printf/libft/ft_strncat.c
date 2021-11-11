/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:54:50 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/11 16:02:46 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strncat(char *s1, char *s2, int n)
{
	char	*s;
	int		len;
	
	s = s1;
	s1 += ft_strlen(s1);
	len = ft_strnlen(s2, n);
	s1[len] = '\0';
	ft_memcpy(s1, s2, len);
	return (s);
}
