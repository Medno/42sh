/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:21:44 by hlely             #+#    #+#             */
/*   Updated: 2018/03/05 18:10:14 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_redir	*handle_simple(t_redir *redir)
{
	int		fd;

	ft_putendl("simple redir");
	if ((fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		redir->fd_out = file_error(redir->file);
		return (redir);
	}
	redir->fd_out = fd;
	return (redir);
}

t_redir	*handle_double(t_redir *redir)
{
	int		fd;

	ft_putendl("double redir");
	if ((fd = open(redir->file, O_RDONLY | O_CREAT | O_APPEND, 0644)) == -1)
	{
		redir->fd_out = file_error(redir->file);
		return (redir);
	}
	redir->fd_out = fd;
	return (redir);
}

t_redir	*handle_simplefd(t_redir *redir)
{
	struct stat	*buf;

	ft_putendl("simplefd redir");
	buf = NULL;
	if (redir->file && ft_strequ(redir->file, "-"))
	{
		redir->fd_out = TOCLOSE;
		return (redir);
	}
	if (redir->file)
		return (handle_simple(redir));
	if (redir->fd_out > 1 && fstat(redir->fd_out, buf) == -1)
	{
		redir->fd_out = BADFD;
		return (redir);
	}
	return (redir);
}

t_redir	*handle_back(t_redir *redir)
{
	int		fd;

	ft_putendl("back redir");
	if ((fd = open(redir->file, O_RDONLY)) == -1)
	{
		redir->fd_out = file_error(redir->file);
		return (redir);
	}
	redir->fd_in = fd;
	return (redir);
}

t_redir	*handle_backfd(t_redir *redir)
{
	int		fd;

	ft_putendl("back redir");
	if (redir->file && ft_strequ(redir->file, "-"))
	{
		redir->fd_out = TOCLOSE;
		return (redir);
	}
	if (redir->file)
	{
		redir->fd_out = AMBIGOUS;
		return (redir);
	}
	if ((fd = open(redir->file, O_RDONLY)) == -1)
	{
		redir->fd_out = file_error(redir->file);
		return (redir);
	}
	redir->fd_in = fd;
	return (redir);
}

t_redir	*handle_heredoc(t_redir *redir)
{
	ft_putendl("heredoc");
	return (redir);
}
