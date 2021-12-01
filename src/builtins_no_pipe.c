/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_no_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/12/01 18:19:06 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_quote(char **commands, t_cmd *cmd, size_t i, int j)
{
    char    c;

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
    else
        write(1, &commands[i][j++], 1);
    return (j);
}

int	ft_export(char *str)
{
	char	**split_str;
	t_cmd   *cmd;
	int		i;
	int		j;

	if (str[1])
	{
		cmd = new_cmd();
		split_str = ft_split(str, '=');
		i = 1;
		while ((int)ft_array_size(split_str) > i)
	    {
	        j = 0;
	        while ((int)ft_strlen(split_str[i]) > j && split_str[i])
	            j = ft_quote(split_str, cmd, i, j);
	        if ((int)ft_array_size(split_str) - 1 != i && cmd->dollar_fail == 0)
	            ft_strncat(cmd->line, &split_str[i][j++], 1);
	        i++;
	    }
		ft_setenv(split_str[0], cmd->line, 1);
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
	if (!ft_strcmp(line, ""))
		return (0);
	else
	{
		add_history(g_mini.line);
		commands = ft_split_minishell(line);
		if (commands == NULL)
			return (0);
		if (!ft_strcmp(commands[0], "cd"))
		{
			ft_cd(commands[1], -1);
			return (ft_frlloc(commands));
		}
		if (!ft_strcmp(commands[0], "export"))
		{
			ft_export(line);
			return (ft_frlloc(commands));
		}
		if (!ft_strcmp(commands[0], "unset"))
		{
			ft_buil_unset(commands[1]);
			return (ft_frlloc(commands));
		}
		ft_frlloc(commands);
		return (0);
	}
}
