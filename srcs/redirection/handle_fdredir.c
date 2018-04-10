/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fdredir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 10:44:14 by hlely             #+#    #+#             */
/*   Updated: 2018/04/10 14:04:10 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_redir	*closefd(t_redir *redir)
{
	redir->fd_in = (redir->fd_in == -1) ? 1 : redir->fd_in;
	close(redir->fd_in);
	redir->fd_out = TOCLOSE;
	return (redir);
}

t_redir	*handle_simplefd(t_redir *redir)
{
	struct stat	buf;
	char		*tmp;

	if (redir->file && ft_strequ(*redir->file, "-"))
		closefd(redir);
	if (redir->file && !ft_isdigit(**redir->file) && **redir->file != '-')
	{
		which_error(AMBIGOUS, *redir->file);
		return (NULL);
	}
	if (redir->fd_in == -1)
		return (handle_allfd(redir));
	if (redir->file && ft_isdigit(**redir->file) && ft_strchr(*redir->file, '-'))
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
