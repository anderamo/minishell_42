/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/11 16:59:02 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->options = 0;
	cmd->args = NULL;
	cmd->line = ft_calloc(BUFF, sizeof(char));
	if (!cmd->line)
	{
		free(cmd->line);
		return (NULL);
	}
	return (cmd);
}

void	ft_print_echo(t_cmd *cmd)
{
	if(cmd->options == 1)
		ft_printf("%s\0", cmd->line);
	else
		ft_printf("%s\n", cmd->line);
}

void	ft_echo(char **commands)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	cmd = new_cmd();;
	i = 1;
	while(commands[i])
	{
		if (i == 1 && !ft_strcmp(commands[i], "-n"))
		{
			cmd->options = 1;
			i++;
		}
		j = 0;
		while (commands[i][j])
    	{
        	if (commands[i][j] == '\'' || commands[i][j] == '\"')
				j = copy_quote(cmd->line, commands[i], 0);
			else
				ft_strncat(cmd->line, &commands[i][j++], 1);
    	}
		ft_strncat(cmd->line, " ", 1);
		i++;
	}
	ft_print_echo(cmd);
}

int	builtins(char **commands)
{
	if (!ft_strcmp(commands[0], "echo"))
	{
		ft_echo(commands);
		return (1);
	}
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
