/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:13:46 by hlely             #+#    #+#             */
/*   Updated: 2018/04/21 12:43:14 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		file_error(char *file)
{
	if (access(file, F_OK) == -1)
		return (NOSUCHFILE);
	else if (access(file, F_OK | R_OK) == -1)
		return (NOPERM);
	return (OPENFAIL);
}

t_redir	*which_error(int error, char *err_file)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	if (error == BADFD && !err_file)
		ft_printf_fd(STDERR_FILENO, "Bad file descriptor\n");
	else if (error == BADFD)
		ft_printf_fd(STDERR_FILENO, "%s: Bad file descriptor\n", err_file);
	else if (error == NOSUCHFILE)
		ft_printf_fd(STDERR_FILENO,
				"%s: No such file or directory\n", err_file);
	else if (error == NOPERM)
		ft_printf_fd(STDERR_FILENO, "%s: Permission denied\n", err_file);
	else if (error == OPENFAIL)
		ft_printf_fd(STDERR_FILENO, "%s: failed to open\n", err_file);
	else if (error == AMBIGOUS)
		ft_printf_fd(STDERR_FILENO, "ambiguous redirection\n");
	else
		ft_putendl_fd("File number expected", STDERR_FILENO);
	return (NULL);
}

t_redir	*backup_error(void)
{
	ft_printf_fd(STDERR_FILENO,
			"42sh : can't use fd from 10 to 12\n");
	return (NULL);
}
