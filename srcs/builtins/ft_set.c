/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 11:56:55 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 14:42:23 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_set(t_env *loc_env, t_env *new_env, char **arg)
{
	if (!arg[1])
	{
		ft_print_env(new_env);
		ft_print_env(loc_env);
	}
	else if (ft_strequ(arg[1], "--loc"))
		ft_print_env(loc_env);
	else
	{
		ft_printf_fd(STDERR_FILENO, "SET is not supporting option yet\n");
		ft_printf_fd(STDERR_FILENO, "--loc to print only locale variable\n");
		return (1);
	}
	return (0);
}
