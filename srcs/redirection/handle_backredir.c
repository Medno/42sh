/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backredir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:44:15 by hlely             #+#    #+#             */
/*   Updated: 2018/04/20 09:43:09 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_redir	*handle_backfd(t_redir *redir)
{
	struct stat		buf;
	char			*tmp;

	if (redir->file && ft_strequ(*redir->file, "-"))
	{
		redir->fd_in = redir->fd_in == -1 ? STDIN_FILENO : redir->fd_in;
		close(redir->fd_in);
		return (redir);
	}
	if (redir->file)
	{
		which_error(AMBIGOUS, NULL);
		return (NULL);
	}
	if (redir->fd_out > 2 && fstat(redir->fd_out, &buf) == -1)
	{
		tmp = ft_itoa(redir->fd_out);
		which_error(BADFD, tmp);
		ft_strdel(&tmp);
		return (NULL);
	}
	redir->fd_in = (redir->fd_in == -1) ? 0 : redir->fd_in;
	dup2(redir->fd_out, redir->fd_in);
	redir->fd_out = -1;
	return (redir);
}

t_redir	*handle_back(t_redir *redir)
{
	int		fd;

	if (!redir->file)
	{
		redir->file = ft_memalloc(sizeof(char*) * 2);
		*redir->file = ft_itoa(redir->fd_out);
		redir->fd_out = -1;
	}
	if ((fd = open(*redir->file, O_RDONLY)) == -1)
	{
		which_error(file_error(*redir->file), *redir->file);
		return (NULL);
	}
	redir->fd_out = fd;
	dup2(fd, redir->fd_in);
	return (redir);
}

t_redir	*handle_rw(t_redir *redir)
{
	int		fd;

	if (!redir->file)
	{
		redir->file = ft_memalloc(sizeof(char*) * 2);
		*redir->file = ft_itoa(redir->fd_out);
		redir->fd_out = -1;
	}
	redir->fd_in = (redir->fd_in == -1) ? 0 : redir->fd_in;
	if ((fd = open(*redir->file, O_RDWR | O_CREAT, 0644)) == -1)
	{
		which_error(file_error(*redir->file), *redir->file);
		return (NULL);
	}
	dup2(fd, redir->fd_in);
	redir->fd_out = fd;
	return (redir);
}
