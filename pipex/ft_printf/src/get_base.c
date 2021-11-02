/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:32:10 by aamorin-          #+#    #+#             */
/*   Updated: 2021/08/30 15:05:22 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*get_base(unsigned long number, int base)
{
	unsigned long		hexa_number;
	int					i;
	char				*str;

	hexa_number = number;
	i = 0;
	if (hexa_number == 0)
		return (ft_strdup("0"));
	while (hexa_number != 0)
	{
		hexa_number /= base;
		i++;
	}
	str = malloc(i + 1);
	str[i] = '\0';
	while (number != 0)
	{
		if ((number % base) < 10)
			str[i - 1] = (number % base) + 48;
		else
			str[i - 1] = (number % base) + 55;
		number /= base;
		i--;
	}
	return (str);
}
