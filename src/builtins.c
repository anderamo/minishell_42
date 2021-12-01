/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/30 19:53:01 by migarcia         ###   ########.fr       */
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
	cmd->dollar_fail = 0;
	cmd->args = NULL;
	cmd->line = ft_calloc(BUFF, sizeof(char));
    if (!cmd->line)
    {
        free(cmd->line);
        return (NULL);
    }
	return (cmd);
}

int	ft_dollar(t_cmd *cmd, char *src, char c, int j)
{
	char	*dst;

	cmd->dollar_fail = 0;
	if (c == '\"' && src[j] != ' ' && src[j] != '\0')
	{
		if (src[j] == '?')
		{
			write(1, g_mini.error, ft_strlen(g_mini.error));
			return (2);
		}
		else
		{
			dst = find_env(src, j);
			if (dst)
				write(1, dst, ft_strlen(dst));
			else
				cmd->dollar_fail = 1;
			return (env_len(src, j));
		}
	}
	else
	{
		write(1, "$", 1);
		return (0);
	}
}

void	ft_echo(char **commands, t_cmd *cmd, size_t i)
{
	int		j;

	if (ft_array_size(commands) > i && !ft_strcmp(commands[i], "-n"))
	{
		cmd->options = 1;
		i++;
	}
	while (ft_array_size(commands) > i)
	{
		j = 0;
		while ((int)ft_strlen(commands[i]) > j && commands[i][j])
			j = ft_copy_quote(commands, cmd, i, j);
		if (ft_array_size(commands) - 1 != i && cmd->dollar_fail == 0)
			write (1, " ", 1);
		i++;
	}
}

int	builtins(char **commands)
{
	t_cmd	*cmd;

	if (!ft_strcmp(commands[0], "echo"))
	{
		cmd = new_cmd();
		g_mini.error = ft_itoa(g_mini.last_error);
		ft_echo(commands, cmd, 1);
		if (cmd->options == 0)
			ft_printf("\n");
		else
			ft_printf("\0");
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
