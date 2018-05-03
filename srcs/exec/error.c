/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:47:26 by hlely             #+#    #+#             */
/*   Updated: 2018/05/03 14:52:52 by hlely            ###   ########.fr       */
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
	return (127);
}

void	error_execve(void)
{
	ft_printf_fd(STDERR_FILENO, "42sh: can't execute command\n");
	exit(EXIT_FAILURE);
}

void	signal_error(int status, pid_t pid)
{
	int		signal;

	signal = WTERMSIG(status);
	if (signal == SIGFPE)
		ft_printf_fd(STDERR_FILENO,
				"%d	Floating point exception: %d\n", pid, signal);
	else if (signal == SIGSEGV)
		ft_printf_fd(STDERR_FILENO,
				"%d	Segmentation fault: %d\n", pid, signal);
	else if (signal == SIGABRT)
		ft_printf_fd(STDERR_FILENO,
				"%d	Abort trap: %d\n", pid, signal);
	else if (signal == SIGBUS)
		ft_printf_fd(STDERR_FILENO,
				"%d	Bus error: %d\n", pid, signal);
	g_status = 128 + signal;
}
