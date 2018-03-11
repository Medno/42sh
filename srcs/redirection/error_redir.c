/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:13:46 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 14:41:36 by hlely            ###   ########.fr       */
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

void	which_error(int error, char *err_file)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	if (error == BADFD)
	{
		ft_putstr_fd(err_file, STDERR_FILENO);
		ft_putendl_fd(": Bad file descriptor", STDERR_FILENO);
	}
	else if (error == NOSUCHFILE)
	{
		ft_putstr_fd(err_file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else if (error == NOPERM)
	{
		ft_putstr_fd(err_file, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else if (error == OPENFAIL)
	{
		ft_putstr_fd(err_file, STDERR_FILENO);
		ft_putendl_fd(": failed to open", STDERR_FILENO);
	}
	else
		ft_putendl_fd("File number expected", STDERR_FILENO);
}
