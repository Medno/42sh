/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:27:39 by hlely             #+#    #+#             */
/*   Updated: 2018/03/21 13:19:08 by hlely            ###   ########.fr       */
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

int			check_p(t_init *init, char **arg)
{
	if (arg[1] && arg[2])
		return (switch_loc_to_env(init, arg + 1));
	ft_print_env(init->new_env, '"');
	return (0);
}

int			ft_export(t_init *init, char ***entry)
{
	char	**arg;
	int		flags;
	char	c;

	flags = 0;
	c = 0;
	arg = *entry;
	reset_ft_opt();
	while ((c = ft_getopt(ft_tablen(arg), arg, "np")) != -1)
	{
		if (ft_strchr("np", c))
			flags = set_bits(c, flags);
		else if (c == '?')
			return (export_usage());
	}
	if (flags == 1)
		return (check_p(init, arg));
	if (flags & 2)
		return (switch_env_to_loc(init, arg));
	else
		return (switch_loc_to_env(init, arg));
	return (0);
}
