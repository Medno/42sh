/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:21:56 by hlely             #+#    #+#             */
/*   Updated: 2018/04/16 12:21:57 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		export_usage(void)
{
	ft_printf_fd(STDERR_FILENO, "export: usage: [-n] [name[=value] ...]");
	ft_printf_fd(STDERR_FILENO, " or export -p\n");
	return (1);
}

int		not_an_identifier(char *function, char *arg)
{
	ft_printf_fd(STDERR_FILENO,
			"42sh : %s: `%s': not a valid identifier\n", function, arg);
	return (0);
}

int		read_only_error(char *arg, int free)
{
	if (free)
		ft_strdel(&arg);
	ft_printf_fd(STDERR_FILENO, "42sh : %s: readonly variable\n", arg);
	return (0);
}
