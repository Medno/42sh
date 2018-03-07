/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:21:44 by hlely             #+#    #+#             */
/*   Updated: 2018/03/07 16:34:15 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_redir	*handle_simple(t_redir *redir)
{
	int		fd;

	if (!redir->file)
		redir->file = ft_itoa(redir->fd_out);
	if ((fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		which_error(file_error(redir->file), redir->file);
		return (NULL);
	}
	dup2(fd, redir->fd_in);
	redir->fd_out = fd;
	return (redir);
}

t_redir	*handle_double(t_redir *redir)
{
	int		fd;

	if ((fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
	{
		which_error(file_error(redir->file), redir->file);
		return (NULL);
	}
	dup2(fd, STDOUT_FILENO);
	redir->fd_out = fd;
	return (redir);
}

t_redir	*handle_allfd(t_redir *redir)
{
	int		fd;

	if ((fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		which_error(file_error(redir->file), redir->file);
		return (NULL);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	redir->fd_out = fd;
	return (redir);
}

t_redir	*handle_closingfd(t_redir *redir)
{
	struct stat	buf;
	char		*tmp;

	redir->fd_out = ft_atoi(redir->file);
	if (redir->fd_out > 2 && fstat(redir->fd_out, &buf) == -1)
	{
		tmp = ft_itoa(redir->fd_out);
		which_error(BADFD, tmp);
		ft_strdel(&tmp);
		return (NULL);
	}
	dup2(redir->fd_out, redir->fd_in);
	close(redir->fd_out);
	return (redir);
}

t_redir	*handle_simplefd(t_redir *redir)
{
	struct stat	buf;
	char		*tmp;

	if (redir->file && ft_strequ(redir->file, "-"))
	{
		redir->fd_in = (redir->fd_in == -1) ? 1 : redir->fd_in;
		close(redir->fd_in);
		redir->fd_out = TOCLOSE;
		return (redir);
	}
	if (redir->file && !ft_isdigit(*redir->file))
		return (handle_allfd(redir));
	if (redir->file && ft_isdigit(*redir->file) && ft_strchr(redir->file, '-'))
		return (handle_closingfd(redir));
	if (redir->fd_out > 2 && fstat(redir->fd_out, &buf) == -1)
	{
		tmp = ft_itoa(redir->fd_out);
		which_error(BADFD, tmp);
		ft_strdel(&tmp);
		return (NULL);
	}
	dup2(redir->fd_out, redir->fd_in);
	return (redir);
}

t_redir	*handle_back(t_redir *redir)
{
	int		fd;

	if ((fd = open(redir->file, O_RDONLY)) == -1)
	{
		which_error(file_error(redir->file), redir->file);
		return (NULL);
	}
	redir->fd_in = fd;
	dup2(fd, redir->fd_in);
	return (redir);
}

t_redir	*handle_backfd(t_redir *redir)
{
	struct stat		*buf;
	char			*tmp;

	buf = NULL;
	if (redir->file && ft_strequ(redir->file, "-"))
	{
		redir->fd_out = TOCLOSE;
		close(redir->fd_in);
		return (redir);
	}
	if (redir->file)
	{
		which_error(AMBIGOUS, NULL);
		return (NULL);
	}
	if (redir->fd_out > 2 && fstat(redir->fd_out, buf) == -1)
	{
		tmp = ft_itoa(redir->fd_out);
		which_error(BADFD, tmp);
		ft_strdel(&tmp);
		return (NULL);
	}
	redir->fd_in = (redir->fd_in == -1) ? 0 : redir->fd_in;
	dup2(redir->fd_out, redir->fd_in);
	return (redir);
}

t_redir	*handle_heredoc(t_redir *redir)
{
	ft_putendl("heredoc");
	return (redir);
}

t_redir	*handle_redirall(t_redir *redir)
{
	int		fd;

	if (!redir->file)
		redir->file = ft_itoa(redir->fd_out);
	if (ft_strequ(redir->file, "-") && redir->fd_in != -1)
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		return (redir);
	}
	if ((fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		which_error(file_error(redir->file), redir->file);
		return (NULL);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	return (redir);
}
