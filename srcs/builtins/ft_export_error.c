/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:21:56 by hlely             #+#    #+#             */
/*   Updated: 2018/03/14 16:27:29 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		export_usage(char *arg)
{
	ft_printf_fd(STDERR_FILENO, "42sh : export: %s: invalid option\n", arg);
	ft_printf_fd(STDERR_FILENO, "export: usage: [-n] [name[=value]] ");
	ft_printf_fd(STDERR_FILENO, "or export -p\n");
	return (1);
}
