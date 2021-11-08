/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/07 18:47:42 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
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

void	ft_cd(char *next_path)
{
	char    **split;
	int		i;

	if (!next_path)
	{
		while (g_mini.env[i])
    	{
        	split = ft_split(g_mini.env[i], '=');
        	if (!strcmp(split[0], "HOME"))
            	break;
        	ft_frlloc(split);
        	i++;
    	}
		chdir(split[1]);
		ft_frlloc(split);
		ft_pwd(1);
	}
	else
	{
		chdir(next_path);
		ft_pwd(1);
	}
}

void	ft_export(char *str)
{
	char	**split_str;
	int		i;

	if (str)
	{
		split_str = ft_split(str, '=');
		ft_setenv(split_str[0], split_str[1], 1); 
		ft_frlloc(split_str);
	}
	else
		printf("ERROR: Wrong export format");
}

char	**ft_unset(char *str)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char*) * (ft_array_size(g_mini.env)));
	if(!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_array_size(g_mini.env))
	{
		if (!strncmp(g_mini.env[i], str, ft_strlen(str)))
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

int	builtins(char *line)
{
	char	**commands;
	char	**new_env;

	if (!ft_strcmp(line, ""))
		return (0);
	else
	{
		commands = ft_split_comma(line, ' ');
		if (!ft_strcmp(commands[0], "pwd"))
		{
			ft_pwd(0);
			printf("\n");
			return (1);
		}
		if (!ft_strcmp(commands[0], "cd"))
		{
			ft_cd(commands[1]);
			return (1);
		}
		if (!ft_strcmp(commands[0], "env"))
		{
			ft_print_env();
			return (1);
		}
		if (!ft_strcmp(commands[0], "export"))
		{
			ft_export(commands[1]);
			return (1);
		}
		if (!ft_strcmp(commands[0], "unset"))
		{
			new_env = ft_unset(commands[1]);
			if (!new_env)
				return (1);
			ft_frlloc(g_mini.env);
			g_mini.env = new_env;
			return (1);
		}
		return (0);
	}
}
