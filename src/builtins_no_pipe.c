/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/11 16:59:29 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *next_path, int i)
{
	char	**split;

	if (!next_path || !ft_strcmp(next_path, "~"))
	{
		while (g_mini.env[++i])
		{
			split = ft_split(g_mini.env[i], '=');
			if (!strcmp(split[0], "HOME"))
				break;
			ft_frlloc(split);
		}
		chdir(split[1]);
		ft_frlloc(split);
	}
	else
	{
		if(chdir(next_path))
		{
			perror("chdir");
			g_mini.last_error = 1;
		}
	}
	ft_pwd(1);
}

int	ft_export(char *str)
{
	char	**split_str;

	if (str)
	{
		split_str = ft_split(str, '=');
		ft_setenv(split_str[0], split_str[1], 1);
		ft_frlloc(split_str);
	}
	else
		printf("ERROR: Wrong export format\n");
	return (1);
}

char	**ft_unset(char *str)
{
	char		**new_env;
	size_t		i;
	int			j;

	new_env = malloc(sizeof(char*) * (ft_array_size(g_mini.env)));
	if(!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_array_size(g_mini.env))
	{
		if (!ft_strncmp(g_mini.env[i], str, ft_strlen(str)))
			i++;
		if (!g_mini.env[i])
			break;
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

int	builtins_no_pipe(char *line)
{
	char **commands;

	if (!ft_strcmp(line, ""))
        return (0);
    else
    {
		add_history(line);
		commands = ft_split(line, ' ');
		if (!ft_strcmp(commands[0], "cd"))
		{
			ft_cd(commands[1], -1);
			return (1);
		}
		if (!ft_strcmp(commands[0], "export"))
			return (ft_export(commands[1]));
		if (!ft_strcmp(commands[0], "unset"))
			return (ft_buil_unset(commands[1]));
		return (0);
	}
}
