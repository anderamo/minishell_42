/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_no_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:35 by migarcia          #+#    #+#             */
/*   Updated: 2021/12/08 09:08:52 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quote(char **str, t_cmd *cmd)
{
	char	c;

	if (**str == '\'' || **str == '\"')
	{
		c = **str;
		*str = *str + 1;
		while (**str != '\0' && **str != c)
		{
			ft_strncat(cmd->line, *str, 1);
			*str = *str + 1;
		}
	}
}

void	ft_export(char *str)
{
	char	**split;
	t_cmd	*cmd;

	if (ft_strchr(str, '='))
	{
		if (isquote(str, ft_strlen(str) - ft_strlen(ft_strchr(str, '='))) == -1)
			return ;
		cmd = new_cmd();
		split = ft_split(str, '=');
		while (*str != '=')
			str++;
		while (*(++str) != '\0')
		{
			if (*str == '\'' || *str == '\"')
				ft_quote(&str, cmd);
			else
				ft_strncat(cmd->line, str, 1);
		}
		ft_setenv(split[0], cmd->line, 1);
		ft_frlloc(split);
		free(cmd->line);
		free(cmd);
	}
	g_mini.last_error = 0;
}

char	**ft_unset(char *str, int count, size_t i, int j)
{
	char		**new_env;

	new_env = malloc(sizeof(char *) * (ft_array_size(g_mini.env)));
	if (!new_env)
		return (NULL);
	while (i < ft_array_size(g_mini.env))
	{
		if (!ft_strncmp(g_mini.env[i], str, ft_strlen(str)))
			i++;
		else
			count++;
		if (!g_mini.env[i])
			break ;
		new_env[j] = ft_strdup(g_mini.env[i]);
		i++;
		j++;
	}
	if (count == (int)ft_array_size(g_mini.env))
	{
		ft_frlloc_n(new_env, i);
		return (NULL);
	}
	new_env[j] = NULL;
	return (new_env);
}

int	ft_buil_unset(char *command)
{
	char	**new_env;

	g_mini.last_error = 0;
	if (!command)
		return (1);
	new_env = ft_unset(command, 0, 0, 0);
	if (!new_env)
		return (1);
	ft_frlloc(g_mini.env);
	g_mini.env = new_env;
	return (0);
}

int	builtins_no_pipe(char *line, char **com)
{
	if (!ft_strcmp(com[0], "cd"))
	{
		ft_cd(com[1], -1);
		return (ft_frlloc(com));
	}
	if (!ft_strcmp(com[0], "export"))
	{
		if (!com[1] || !ft_strncmp(com[1], "=", 1))
		{
			printf("ERROR: Wrong export format\n");
			g_mini.last_error = 1;
		}
		else if (!ft_strncmp(com[0], "\'", 1) || !ft_strncmp(com[0], "\"", 1))
			ft_export(line);
		else
			ft_export(com[1]);
		return (ft_frlloc(com));
	}
	if (!ft_strcmp(com[0], "unset"))
	{
		ft_buil_unset(com[1]);
		return (ft_frlloc(com));
	}
	return (0);
}
