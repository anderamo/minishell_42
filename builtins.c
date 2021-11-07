/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/07 15:46:02 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#define BUFF 1024

void	ft_pwd(void)
{
	char	path[BUFF];

	if (!getcwd(path, BUFF))
		perror("getcwd");
	else
		printf("%s", path);
}

void	ft_cd(char *next_path)
{

	chdir(next_path);
	set_path();
}

int	builtins(char *line)
{
	char **commands;

	if (!ft_strcmp(line, ""))
		return (0);
	else
	{
		commands = ft_split_comma(line, ' ');
		if (!ft_strcmp(commands[0], "pwd"))
		{
			ft_pwd();
			printf("\n");
			return (1);
		}
		if (!ft_strcmp(commands[0], "cd"))
		{
			ft_cd(commands[1]);
			return (1);
		}
		return (0);
	}
}
