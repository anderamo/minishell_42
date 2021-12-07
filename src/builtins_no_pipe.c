/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_no_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/12/06 19:45:45 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote(char **commands, t_cmd *cmd, size_t i, int j)
{
	char	c;

	if (commands[i][j] == '\'' || commands[i][j] == '\"')
	{
		c = commands[i][j];
		j++;
		while ((int)ft_strlen(commands[i]) > j)
		{
			if (commands[i][j] != c)
				ft_strncat(cmd->line, &commands[i][j], 1);
			if ((int)ft_strlen(commands[i]) > j && commands[i][j] == c)
				j++;
			j++;
		}
	}
	return (j);
}

void	ft_export(char *str, int i, int j)
{
	char	**split;
	t_cmd	*cmd;

	if (str[1])
	{
		cmd = new_cmd();
		if (ft_strchr(str, '='))
		{
			split = ft_split(str, '=');
			while ((int)ft_array_size(split) > ++i)
			{
				j = 0;
				if (split[i][j] == '\'' || split[i][j] == '\"')
					j = ft_quote(split, cmd, i, j);
				else
					ft_strncat(cmd->line, split[i], ft_strlen(split[i]));
			}
			ft_setenv(split[0], cmd->line, 1);
			ft_frlloc(split);
		}
		free(cmd->line);
		free(cmd);
	}
	else
		printf("ERROR: Wrong export format\n");
}

char	**ft_unset(char *str)
{
	char		**new_env;
	size_t		i;
	int			j;

	new_env = malloc(sizeof(char *) * (ft_array_size(g_mini.env)));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_array_size(g_mini.env))
	{
		if (!ft_strncmp(g_mini.env[i], str, ft_strlen(str)))
			i++;
		if (!g_mini.env[i])
			break ;
		new_env[j] = ft_strdup(g_mini.env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	ft_buil_unset(char *command)
{
	char	**new_env;

	if (!ft_strcmp(command, "PWD"))
	{
		printf("Error: impossible to unset 'PWD'.\n");
		return (1);
	}
	new_env = ft_unset(command);
	if (!new_env)
		return (1);
	ft_frlloc(g_mini.env);
	g_mini.env = new_env;
	return (1);
}

int	builtins_no_pipe(char *line, char **commands)
{
	if (!ft_strcmp(commands[0], "cd"))
	{
		ft_cd(commands[1], -1);
		return (ft_frlloc(commands));
	}
	if (!ft_strcmp(commands[0], "export"))
	{
		if (!ft_strncmp(commands[0], "\'", 1)
			|| !ft_strncmp(commands[0], "\"", 1))
			ft_export(line, 0, 0);
		else
			ft_export(commands[1], 0, 0);
		return (ft_frlloc(commands));
	}
	if (!ft_strcmp(commands[0], "unset"))
	{
		ft_buil_unset(commands[1]);
		return (ft_frlloc(commands));
	}
	return (0);
}
