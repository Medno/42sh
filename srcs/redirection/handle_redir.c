/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:21:44 by hlely             #+#    #+#             */
/*   Updated: 2018/04/21 12:31:23 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_redir	*handle_simple(t_redir *redir)
{
	int		fd;

	if (!redir->file)
	{
		redir->file = ft_memalloc(sizeof(char*) * 2);
		*redir->file = ft_itoa(redir->fd_out);
	}
	if ((fd = open(*redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		which_error(file_error(*redir->file), *redir->file);
		return (NULL);
	}
	dup2(fd, redir->fd_in);
	redir->fd_out = fd;
	return (redir);
}

t_redir	*handle_allfd(t_redir *redir)
{
	int			fd;
	struct stat	buf;
	char		*tmp;

	if (redir->fd_out >= 0)
	{
		fd = redir->fd_out;
		if (fstat(fd, &buf) == -1)
		{
			tmp = ft_itoa(redir->fd_out);
			which_error(BADFD, tmp);
			ft_strdel(&tmp);
			return (NULL);
		}
	}
	else if ((fd = open(*redir->file, O_WRONLY |
					O_CREAT | O_TRUNC, 0644)) == -1)
		return (which_error(file_error(*redir->file), *redir->file));
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	redir->fd_out = -1;
	return (redir);
}

t_redir	*handle_closingfd(t_redir *redir)
{
	struct stat	buf;
	char		*tmp;

	redir->fd_out = ft_atoi(*redir->file);
	if (redir->fd_out > 2 && fstat(redir->fd_out, &buf) == -1)
	{
		tmp = ft_itoa(redir->fd_out);
		which_error(BADFD, tmp);
		ft_strdel(&tmp);
		return (NULL);
	}
	dup2(redir->fd_out, redir->fd_in);
	close(redir->fd_out);
	redir->fd_out = -1;
	return (redir);
}

t_redir	*handle_redirall(t_redir *redir)
{
	int		fd;

	if (!redir->file)
	{
		redir->file = ft_memalloc(sizeof(char*) * 2);
		*redir->file = ft_itoa(redir->fd_out);
	}
	if (ft_strequ(*redir->file, "-") && redir->fd_in != -1)
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		return (redir);
	}
	if ((fd = open(*redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		which_error(file_error(*redir->file), *redir->file);
		return (NULL);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	return (redir);
}
