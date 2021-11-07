#include "includes/minishell.h"

int	init_env(t_mini g_mini, char **env)
{
	int		i;

	if (!env || !(*env))
		return (0);
	g_mini.env = (char **)malloc(sizeof(char *) * (ft_array_size(env) + 2));
	if (!(g_mini.env))
		return (0);
//	g_mini.env = env;
	i = 0;
	while (env[i])
	{
		g_mini.env[i] = ft_strdup(env[i]);
		if (!g_mini.env[i])
		{
			ft_frlloc_n((void **)g_mini.env, i);
			return (0);
		}
		i++;
	}
//	g_mini.env[i] = NULL;
//	g_mini.last_argument = ft_strdup("minishell");
//	ft_setenv(g_mini, "_", g_mini.last_argument, 1);
	i = -1;
	while(g_mini.env[i])
        printf("%s\n", g_mini.env[++i]);
	return (1);
}
