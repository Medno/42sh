/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:27:39 by hlely             #+#    #+#             */
/*   Updated: 2018/05/02 12:18:38 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			export_equal(t_init *init, char *arg, int whereto)
{
	char	*name;
	char	*value;

	name = ft_strsub(arg, 0, equ_index(arg, '='));
	value = ft_strchr(arg, '=') + 1;
	if (whereto == TOENV)
	{
		ft_setenv(&init->new_env, name, value);
		if (is_in_env(init->loc_env, name))
			ft_unsetenv(&init->loc_env, name);
	}
	else
	{
		ft_setenv(&init->loc_env, name, value);
		if (is_in_env(init->new_env, name))
			ft_unsetenv(&init->new_env, name);
	}
	ft_strdel(&name);
	return (0);
}

static int	set_bits(char c, int flag)
{
	if (c == 'p')
		flag |= 1;
	else if (c == 'n')
		flag |= 2;
	return (flag);
}

static int	check_p(t_init *init, char **arg)
{
	if (arg && arg[0])
		return (switch_loc_to_env(init, arg));
	ft_print_env(init->new_env, '"');
	return (0);
}

static int	router(t_init *init, char **arg, int flags)
{
	if (flags == 1 || !arg[0])
		return (check_p(init, arg));
	if (flags & 2)
		return (switch_env_to_loc(init, arg));
	else
		return (switch_loc_to_env(init, arg));
	return (0);
}

int			ft_export(t_init *init, char ***entry)
{
	char	c;
	char	**arg;
	int		i;
	int		flags;

	flags = 0;
	c = 0;
	arg = *entry;
	reset_ft_opt();
	if (arg && (!(arg)[1] ||
				(arg[1] && ft_tablen(arg) == 2 && ft_strequ(arg[1], "--"))))
	{
		ft_print_env(init->new_env, '\'');
		return (0);
	}
	while ((c = ft_getopt(ft_tablen(arg), arg, "np")) != -1)
	{
		if (ft_strchr("np", c))
			flags = set_bits(c, flags);
		else if (c == '?')
			return (export_usage());
	}
	i = inc_opt(arg);
	return (router(init, arg + i, flags));
}
