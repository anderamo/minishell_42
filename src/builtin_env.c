/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:54:55 by migarcia          #+#    #+#             */
/*   Updated: 2021/11/08 09:25:48 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strjoin3(char *a, char *b, char *c)
{
	unsigned int	i;
	char	*dest;

	if (!a || !b || !c)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) + ft_strlen(c)) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (*a)
		dest[i++] = *a++;
    while (*b)
		dest[i++] = *b++;
	while (*c)
		dest[i++] = *c++;
	dest[i] = '\0';
	return (dest);
}

char	**add_new_variable(char *name, char *value)
{
	size_t	i;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (ft_array_size(g_mini.env) + 2));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < ft_array_size(g_mini.env))
	{
		new_env[i] = ft_strdup(g_mini.env[i]);
		if (!new_env[i])
		{
			ft_frlloc_n(new_env, i);
			return (NULL);
		}
	}
	new_env[i] = ft_strjoin3(name, "=", value);
	if (!new_env[i++])
	{
		ft_frlloc_n(new_env, i);
		return (NULL);
	}
	new_env[i] = NULL;
	return (new_env);
}

int	add_new_env(char *name, char *value)
{
	char	**new_env;

	new_env = add_new_variable(name, value);
	if (!new_env)
		return (1);
	ft_frlloc(g_mini.env);
	g_mini.env = new_env;
	return (0);
}

int	ft_setenv(char *name, char *value, int replace)
{
	int		i;
	char	*temp;

	if (!name || !ft_strlen(name) || ft_strchr(name, '='))
		return (1);
	if (replace)
	{
		i = -1;
		while (g_mini.env[++i])
		{
			if (ft_strncmp(g_mini.env[i], name, ft_strlen(name)) == 0)
			{
				temp = ft_strjoin3(name, "=", value);
				if (!temp)
					return (1);
				free(g_mini.env[i]);
				g_mini.env[i] = temp;
				return (0);
			}
		}
	}
	return (add_new_env(name, value));
}

void	ft_print_env(void)
{
	int	i;

	i = 0;
	while (g_mini.env[i])
	{
		printf("---%s\n", g_mini.env[i]);
		i++;
	}
}

/*size_t  ft_len_to_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}


char	*ft_getenv(char *name)
{
	int		i;
	int		j;
	size_t	len;

	if (!name)
		return (NULL);
	//len = ft_strlen(name);
	i = 1;
	//while (g_mini.env[i])
	//{
		//if (ft_strlen(name) >= ft_len_to_char(g_mini.env[i], '=')
		//	&& ft_strncmp(g_mini.env[i], name, len) == 0)
		//{
		//	j = 0;
			while (g_mini.env[i][j] && g_mini.env[i][j] != '=')
			{
				printf("%c", g_mini.env[i][j]);
				j++;
			}
			printf("\n");
			//return (&g_mini.env[i][++j]);
		//}
	//	i++;
	//}
	return (NULL);
}*/
