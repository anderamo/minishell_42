/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:46:00 by aamorin-          #+#    #+#             */
/*   Updated: 2021/11/07 18:47:57 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf/includes/ft_printf.h"
# include <stddef.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include "readline.h"
# include "history.h"
# include "chardefs.h"
# include "keymaps.h"
# include "rlconf.h"
# include "rlstdc.h"
# include "tilde.h"

typedef struct s_mini
{
	char	**env;
	char	*path;
	char	*last_argument;
	char	*current_dir;	
} t_mini;

t_mini g_mini;

void	write_pwd(char **envp);
int		init_env(char **env);
size_t  ft_array_size(char **arr);
char    **ft_frlloc(char **tab);
void    ft_frlloc_n(char **tab, size_t n);
int		ft_setenv(char *name, char *value, int replace);
void    ft_print_env(void);
void	signal_proc();
int		builtins(char *line);
char	*readline(const char *prompt);

#endif
