/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:36:04 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/05 14:59:27 by kyazdani         ###   ########.fr       */
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

//check_fun_env a faire (pour launch binaire, check et toutout)

static int	ft_env_2(t_env *env, char **str, int opt_i)
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
		return (1);
	}
	pathlist = ft_strsplit(ft_getenv(&env, "PATH"), ':');
//	check_fun_env(pathlist, new_tab, &str[i]);
	ft_freetab(new_tab);
	ft_freetab(pathlist);
	return (0);
}

int			ft_env(t_env *env, char **entry)
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
			return (1);
		else if (c == 'i')
			i = 1;
	}
	return (ft_env_2(tmp, &entry[g_optind], i));
}
