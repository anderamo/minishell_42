/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/09 17:55:10 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define BUFF 1024

void	ft_pwd(int print)
{
	char	path[BUFF];

	if (!getcwd(path, BUFF))
		perror("getcwd");
	else
	{
		if (!print)
			printf("%s", path);
		ft_setenv("PWD", path, 1);
	}
}

int	builtins(char **commands)
{
	if (!ft_strcmp(commands[0], "pwd"))
	{
		ft_pwd(0);
		printf("\n");
		return (1);
	}
	if (!ft_strcmp(commands[0], "env"))
	{
		ft_print_env();
		return (1);
	}
	return (0);
}
