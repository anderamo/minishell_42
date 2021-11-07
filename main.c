/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:45:25 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/07 15:46:00 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**ft_frlloc(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

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

	i = get_path(envp);
	j = 0;
	path_split = ft_split(envp[i] + 5, ':');
	while (path_split[j])
	{
		path_split[j] = ft_strjoin(path_split[j], "/");
		path_split[j] = ft_strjoin(path_split[j], command);
		if (!access(path_split[j], F_OK))
			return (path_split[j]);
		j++;
	}
	ft_frlloc(path_split);
	return (NULL);
}

void	write_pwd(char **envp)
{
	int		i;
	char	**split;

	i = 0;
	while (1)
	{
		split = ft_split(envp[i], '=');
		if (!strcmp(split[0], "PWD"))
			break ;
		ft_frlloc(split);
		i++;
	}
	ft_printf("\033[36m%s", split[1]);
	ft_frlloc(split);
}

void	set_path()
{
	char    path[1024];

    if (!getcwd(path, 1024))
        perror("getcwd");
	else
		g_mini.path = path;
	printf("%s",g_mini.path);
}

int	shell(char **commands, char **envp)
{
	char	*bin;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		bin = get_bin_path(envp, commands[0]);
		if (execve(bin, commands, envp) == -1)
		{
			perror("execve");
			ft_frlloc(commands);
			free(bin);
			exit(127);
		}
	}
	else if (pid > 0)
	{
		wait(0);
		return (1);
	}
	else if (pid < 0)
		return (0);
	return (1);
}

int	init_env(char **env)
{
	int	i;

	if (!env)
		return (0);
	g_mini.env = (char **)malloc(sizeof(char *) * ft_array_size(env) + 2);
}

int	main(int a, char **argv, char **env)
{
	char		*line;

	init_env(env);;
//	set_path();
	signal_proc();
	while (1)
	{
		write_pwd(env);
		line = readline(" > \033[0m");
		if (!line)
			exit(1);
		if (!ft_strcmp(line, "exit"))
			break ;
		if (!builtins(line))
		{
			if (ft_strcmp(line, ""))
			{
				add_history(line);
				if (shell(ft_split_comma(line, ' '), env) == 0)
				{
					ft_printf("Error: Shell error");
					break ;
				}
			}
		}
		free(line);
	}
	free(line);
	return (0);
}
