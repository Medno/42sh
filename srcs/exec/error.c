/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:47:26 by hlely             #+#    #+#             */
/*   Updated: 2018/03/15 10:14:07 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_error(int ret, char *str, int print)
{
	if (print)
	{
		if (ret == -1)
			ft_printf_fd(2, "42sh: %s: No such file or directory\n", str);
		else if (ret == -2)
			ft_printf_fd(2, "42sh: %s: Permission denied\n", str);
		else if (ret == -3)
			ft_printf_fd(2, "42sh: %s: is a directory\n", str);
	}
	return (ret);
}

void	exit_error(int ret, char *str)
{
	if (ret == 1)
		ft_printf_fd(STDERR_FILENO, "42sh: %s: command not found\n", str);
	exit(EXIT_FAILURE);
}

int		path_error(char *str)
{
	ft_printf_fd(STDERR_FILENO, "42sh: %s: command not found\n", str);
	return (1);
}

void	error_execve(void)
{
	ft_printf_fd(STDERR_FILENO, "42sh: error with execve\n");
	exit(EXIT_FAILURE);
}
