/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:45:25 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/27 13:31:56 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_path(char **envp)
{
	int		i;
	char	**split;

	i = 0;
	while (1)
	{
		split = ft_split(envp[i], '=');
		if (!strcmp(split[0], "PATH"))
			break ;
		ft_frlloc(split);
		i++;
	}
	ft_frlloc(split);
	return (i);
}

char	*get_bin_path(char **envp, char *command)
{
	char	**path_split;
	int		i;
	int		j;
	char	*bin;

	if (!ft_strncmp(command, "/", 1))
		return (command);
	i = get_path(envp);
	j = -1;
	path_split = ft_split(envp[i] + 5, ':');
	while (path_split[++j])
	{
		path_split[j] = ft_strjoin(path_split[j], "/");
		path_split[j] = ft_strjoin(path_split[j], command);
		if (!access(path_split[j], F_OK))
		{
			bin = ft_strdup(path_split[j]);
			ft_frlloc(path_split);
			return (bin);
		}
	}
	ft_frlloc(path_split);
	return (NULL);
}

int	check_if_exits(t_pipe pipex, int a)
{
	int	i;

	i = 1;
	while (pipex.exe[a].c_split[i] != NULL)
	{
		if (!ft_strncmp(pipex.exe[a].c_split[i], "-", 1))
			return (1);
		if (access(pipex.exe[a].c_split[i], F_OK) == 0)
			i++;
		else
		{
			printf("bash: %s: No such file or directory\n",
				pipex.exe[a].c_split[i]);
			g_mini.last_error = 1;
			return (1);
		}
	}
	return (1);
}

void	write_pwd(void)
{
	int		i;
	char	**split;

	wait(0);
	i = 0;
	while (g_mini.env[i])
	{
		split = ft_split(g_mini.env[i], '=');
		if (!strcmp(split[0], "PWD"))
			break ;
		ft_frlloc(split);
		i++;
	}
	g_mini.prompt = ft_strjoin3("\033[36m", split[1], " > \033[0m");
	ft_frlloc(split);
}

int	main(int a, char **argv, char **env)
{
	init_env(env);
	while (1 || argv || a)
	{
		g_mini.line = readline("minishell > ");
		while (g_mini.line && (ft_isspace(*g_mini.line)))
			g_mini.line++;
		if (!ft_strncmp(g_mini.line, "exit ", 5)
			|| !ft_strcmp(g_mini.line, "exit"))
			break ;
		if (ft_strcmp(g_mini.line, ""))
		{
			if (!builtins_no_pipe(g_mini.line, NULL))
			{
				g_mini.s_pipe = ft_split_pipe(g_mini.line);
				pipex(g_mini.s_pipe, ft_arraybilen(g_mini.s_pipe), -1, 0);
				ft_frlloc(g_mini.s_pipe);
			}
		}
	}
	ft_frlloc(g_mini.env);
	return (0);
}
