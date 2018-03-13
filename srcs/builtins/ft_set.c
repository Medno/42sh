/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 11:56:55 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 16:23:58 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_set(t_init *init, char ***entry)
{
	char **arg;

	arg = *entry;
	if (!arg[1])
	{
		ft_print_env(init->new_env);
		ft_print_env(init->loc_env);
	}
	else if (ft_strequ(arg[1], "--loc"))
		ft_print_env(init->loc_env);
	else
	{
		ft_printf_fd(STDERR_FILENO, "SET is not supporting option yet\n");
		ft_printf_fd(STDERR_FILENO, "--loc to print only locale variable\n");
		return (1);
	}
	return (0);
}
