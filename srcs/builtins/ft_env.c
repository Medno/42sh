/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:36:04 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/27 15:53:40 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern int	g_optind;

static int	print_env_tab(char **arr)
{
	int		i;

	i = -1;
	if (!arr)
		return (1);
	while (arr[++i])
		ft_putendl(arr[i]);
	return (1);
}

//static void check_fun to do again (fork and all)

static void	ft_env_2(t_env *env, char **str, int opt_i)
{
	char	**new_tab;
	char	**pathlist;
	int		i;

	i = -1;
	pathlist = NULL;
	new_tab = NULL;
	if (!opt_i)
		new_tab = put_in_tab(&env);
	while (str[++i] && ft_strchr(str[i], '='))
		new_tab = ft_addstr_tab(new_tab, str[i]);
	if (!str[i] && print_env_tab(new_tab))
	{
		ft_freetab(new_tab);
		return ;
	}
	pathlist = ft_strsplit(ft_getenv(&env, "PATH"), ':');
//	check_fun_env(pathlist, new_tab, &str[i]);
	ft_freetab(new_tab);
	ft_freetab(pathlist);
}

void		ft_env(t_env *env, char **entry)
{
	t_env	*tmp;
	int		c;
	int		i;
	int		len;

	tmp = env;
	i = 0;
	c = 0;
	len = ft_tablen(entry);
	reset_ft_opt();
	while ((c = ft_getopt(len, entry, "i")) != -1)
	{
		if (c == '?' && write(STDERR_FILENO,
			"usage: env [-i] [name=value ...] [utility [argument ...]]\n", 58))
			return ;
		else if (c == 'i')
			i = 1;
	}
	ft_env_2(tmp, &entry[g_optind], i);
}
