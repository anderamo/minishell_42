/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:51:33 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/24 18:57:18 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_old_pwd(void)
{
	int		i;
	char	**split;
	char	*pwd;

	i = 0;
	while (1)
	{
		split = ft_split(g_mini.env[i], '=');
		if (!ft_strcmp(split[0], "OLDPWD"))
		{
			free(g_mini.env[i]);
			pwd = getcwd(NULL, 0);
			g_mini.env[i] = ft_strjoin_no_free("OLDPWD=", pwd);
			free(pwd);
			break ;
		}
		ft_frlloc(split);
		i++;
	}
	ft_frlloc(split);
}

void	ft_cd_home(int i)
{
	char	**split;

	change_old_pwd();
	while (g_mini.env[++i])
	{
		split = ft_split(g_mini.env[i], '=');
		if (!strcmp(split[0], "HOME"))
			break ;
		ft_frlloc(split);
	}
	chdir(split[1]);
	ft_frlloc(split);
}

void	ft_cd_old_pwd(int i)
{
	char	**split;

	while (g_mini.env[++i])
	{
		split = ft_split(g_mini.env[i], '=');
		if (!strcmp(split[0], "OLDPWD"))
			break ;
		ft_frlloc(split);
	}
	printf("%s\n", split[1]);
	chdir(split[1]);
	ft_frlloc(split);
}

void	ft_cd(char *next_path, int i)
{
	if (!next_path || !ft_strcmp(next_path, "~"))
		ft_cd_home(i);
	else if (!ft_strcmp(next_path, "-"))
		ft_cd_old_pwd(i);
	else
	{
		change_old_pwd();
		if (chdir(next_path))
		{
			perror("chdir");
			g_mini.last_error = 1;
		}
	}
	ft_pwd(1);
}