/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 11:56:55 by hlely             #+#    #+#             */
/*   Updated: 2018/05/03 15:29:57 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_set(t_env *loc, t_env *env, char **arg)
{
	if (!arg[1] || (arg[1] && !arg[2] && ft_strequ(arg[1], "--")))
	{
		ft_print_env(env, '\'');
		ft_print_env(loc, '\'');
		return (0);
	}
	else if (arg[1] && ft_strequ(arg[1], "--loc"))
	{
		ft_print_env(loc, '\'');
		return (0);
	}
	else
		ft_printf_fd(STDERR_FILENO, "usage: set [--loc]\n");
	return (1);
}
