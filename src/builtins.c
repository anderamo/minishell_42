/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/17 19:52:04 by aamorin-         ###   ########.fr       */
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

int	ft_dollar(t_cmd *cmd, char *src, char *error)
	{
	int		i;
	char	*dst;

	i = 1;
	if (src[i] == '?')
	{
		strncat(cmd->line, error, ft_strlen(error));
		return (2);
	}
	else
	{
		dst = find_env(&src[i], &i);
		if (dst)
			strncat(cmd->line, dst, ft_strlen(dst));
		else
			strncat(cmd->line, "", 1);
	}
	while (ft_strlen(src) > i && src[i])
		i++;
	return (i);
}

void	ft_echo(char **commands, t_cmd *cmd, char *error, size_t i)
{
	int		j;

	while (ft_array_size(commands) > i && commands[++i])
	{
		if (i == 1 && !ft_strcmp(commands[i], "-n"))
		{
			cmd->options = 1;
			i++;
		}
		j = 0;
		while (ft_strlen(commands[i]) > j && commands[i][j])
		{
			if (commands[i][j] == '\'' || commands[i][j] == '\"')
				j = copy_quote(cmd->line, commands[i], 0, error);
			else if (commands[i][j] == '$')
				j += ft_dollar(cmd, commands[i], error);
			else
				ft_strncat(cmd->line, &commands[i][j++], 1);
		}
		if (ft_array_size(commands) != i + 1)
			ft_strncat(cmd->line, " ", 1);
	}
}

int	builtins(char **commands)
{
	t_cmd	*cmd;

	if (!ft_strcmp(commands[0], "echo"))
	{
		cmd = new_cmd();
		g_mini.error = ft_itoa(g_mini.last_error);
		ft_echo(commands, cmd, g_mini.error, 0);
		if (cmd->options == 0)
			ft_printf("%s\n", cmd->line);
		else
			ft_printf("%s\0", cmd->line);
		free_builtins(cmd);
		return (1);
	}
	if (!ft_strcmp(commands[0], "pwd"))
	{
		ft_pwd(0);
		return (printf("\n"));
	}
	if (!ft_strcmp(commands[0], "$?"))
		return (ft_last_error());
	if (!ft_strcmp(commands[0], "env"))
		return (ft_print_env());
	return (0);
}
