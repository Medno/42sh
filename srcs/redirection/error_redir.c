/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:13:46 by hlely             #+#    #+#             */
/*   Updated: 2018/03/05 20:25:25 by hlely            ###   ########.fr       */
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

int		which_error(int error)
{
	if (error == BADFD)
	{
		ft_putendl_fd("Error: Bad file descriptor", STDERR_FILENO);
		return (1);
	}
	else if (error == NOSUCHFILE)
	{
		ft_putendl_fd("Error: No such file or directory", STDERR_FILENO);
		return (1);
	}
	else if (error == NOPERM)
	{
		ft_putendl_fd("Error: Permission denied", STDERR_FILENO);	
		return (1);
	}
	else if (error == AMBIGOUS)
	{
		ft_putendl_fd("Error: file number expected", STDERR_FILENO);
		return (1);
	}
	else if (error == OPENFAIL)
	{
		ft_putendl_fd("Error: file number expected", STDERR_FILENO);
		return (1);
	}
	return (0);
}
