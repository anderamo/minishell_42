/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:51:33 by aamorin-          #+#    #+#             */
/*   Updated: 2021/12/06 19:57:51 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_old_pwd(void)
{
	int		i;
	char	**split;
	char	*pwd;
	char	*absol;

	i = -1;
	while (g_mini.env[++i])
	{
		split = ft_split(g_mini.env[i], '=');
		if (!ft_strcmp(split[0], "OLDPWD"))
		{
			free(g_mini.env[i]);
			pwd = getcwd(NULL, 0);
			g_mini.env[i] = ft_strjoin_no_free("OLDPWD=", pwd);
			free(pwd);
			ft_frlloc(split);
			return ;
		}
		ft_frlloc(split);
	}
	pwd = getcwd(NULL, 0);
	absol = ft_strjoin_no_free("OLDPWD=", pwd);
	ft_export(absol, 0, 0);
	free(absol);
	free(pwd);
}

void	ft_cd_relative(char *next_path, int i, size_t len)
{
	char	*absol;
	char	*tmp;
	char	**split;

	change_old_pwd();
	len = ft_strlen((char *)next_path);
	tmp = malloc(len + 1);
	ft_memcpy(tmp, ++next_path, len);
	tmp[len] = '\0';
	split = NULL;
	while (g_mini.env[++i])
	{
		split = ft_split(g_mini.env[i], '=');
		if (!ft_strcmp(split[0], "HOME"))
			break ;
		ft_frlloc(split);
	}
	absol = ft_strjoin_no_free(split[1], tmp);
	if (split)
		ft_frlloc(split);
	free(tmp);
	chdir(absol);
	free(absol);
}

void	ft_cd_home(int i)
{
	char	**split;

	change_old_pwd();
	while (g_mini.env[++i])
	{
		split = ft_split(g_mini.env[i], '=');
		if (!ft_strcmp(split[0], "HOME"))
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
		if (!ft_strcmp(split[0], "OLDPWD"))
			break ;
		ft_frlloc(split);
	}
	printf("%s\n", split[1]);
	chdir(split[1]);
	ft_frlloc(split);
}

void	ft_cd(char *next_path, int i)
{
	g_mini.last_error = 0;
	if (!next_path || !ft_strcmp(next_path, "~"))
		ft_cd_home(i);
	else if (!ft_strncmp(next_path, "~/", 2))
		ft_cd_relative(next_path, -1, 0);
	else if (!ft_strcmp(next_path, "-"))
		ft_cd_old_pwd(i);
	else
	{
		if (chdir(next_path))
		{
			perror("chdir");
			g_mini.last_error = 1;
		}
		else
			change_old_pwd();
	}
	ft_pwd(1);
}
