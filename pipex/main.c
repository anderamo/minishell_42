/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 18:22:47 by aamorin-          #+#    #+#             */
/*   Updated: 2021/08/31 13:06:50 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

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

void	dad(int *p, char **argv, char **envp)
{
	int		fd;
	char	**c1_split;
	char	*bin;
	char	*command;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	wait(0);
	close(p[1]);
	dup2(p[0], 0);
	close(p[0]);
	dup2(fd, 1);
	command = ft_strdup(argv[3]);
	c1_split = ft_split_comma(command, ' ');
	bin = get_bin_path(envp, c1_split[0]);
	if (execve(bin, c1_split, envp) == -1)
	{
		ft_frlloc(c1_split);
		free(bin);
	}
	perror("execve");
}


void	child(int *p, char **argv, char **envp, int fd)
{
	char	**c2_split;
	char	*bin;
	char	*command;

	close(p[0]);
	dup2(p[1], 1);
	close(p[1]);
	dup2(fd, 0);
	command = ft_strdup(argv[2]);
	c2_split = ft_split_comma(command, ' ');
	bin = get_bin_path(envp, c2_split[0]);
	if (execve(bin, c2_split, envp) == -1)
	{
		ft_frlloc(c2_split);
		free(bin);
	}
	perror("execve");
}

void	pipex(char **argv, char **envp)
{
	pid_t	pid;
	int		p[2];
	int		fd;

	if (pipe(p) == -1)
		exit (0);
	if (!ft_strncmp(argv[1], "/", 1) || ft_strncmp(argv[1], "/dev/null", 9))
		return ;
	if (pipe(p) == -1)
		exit (0);
	fd = open(argv[1], O_RDONLY, 0);
	if (fd < 0)
		exit (0);
	pid = fork();
	if (pid == 0)
		child(p, argv, envp, fd);
	else if (pid > 0)
		dad(p, argv, envp);
	else if (pid < 0)
		exit (0);
}

int	main(int a, char **argv, char **envp)
{
	if (a == 5)
		pipex(argv, envp);
	else
		exit (1);
	return (0);
}
