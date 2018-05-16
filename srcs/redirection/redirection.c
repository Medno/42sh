/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:50:47 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 12:15:56 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		is_fd_redir(t_redir *redir)
{
	if (ft_strequ(redir->token, ">&") || ft_strequ(redir->token, "<&") ||
			ft_strequ(redir->token, "&>"))
		return (1);
	return (0);
}

static t_redir	*check_redir_error(t_redir *redir)
{
	char	*tmp;

	if (redir->file && ft_tablen(redir->file) > 1)
		return (which_error(AMBIGOUS, NULL));
	if (!redir->file && redir->fd_out == -1)
		return (which_error(AMBIGOUS, NULL));
	if ((redir->fd_in >= 10 && redir->fd_in <= 12) ||
			(is_fd_redir(redir) && redir->fd_out >= 10 && redir->fd_out <= 12))
		return (backup_error());
	if (redir->fd_out < -1 || redir->fd_in < -1)
		return (which_error(BADFD, NULL));
	if (redir->fd_in > 4863)
	{
		tmp = ft_itoa(redir->fd_in);
		which_error(BADFD, tmp);
		ft_strdel(&tmp);
		return (NULL);
	}
	return (redir);
}

t_redir			*handle_redir(t_init *init, t_redir *redir)
{
	if (!check_redir_error(redir))
		return (NULL);
	else if (is_in_pipelist(init->pipe, redir->fd_out))
		return (which_error(BADFD, NULL));
	else if (ft_strequ(redir->token, ">"))
		redir = handle_simple(redir);
	else if (ft_strequ(redir->token, ">&"))
		redir = handle_simplefd(init, redir);
	else if (ft_strequ(redir->token, "<&"))
		redir = handle_backfd(redir);
	else if (ft_strequ(redir->token, ">>"))
		redir = handle_double(redir);
	else if (ft_strequ(redir->token, "<"))
		redir = handle_back(redir);
	else if (ft_strequ(redir->token, "&>"))
		redir = handle_redirall(redir);
	else if (ft_strequ(redir->token, "<>"))
		redir = handle_rw(redir);
	return (redir);
}

int				redirection(t_init *init, t_cmd *cmd)
{
	t_cmd	*tmp1;
	t_redir	*tmp;

	tmp1 = cmd;
	tmp = tmp1->redir;
	while (tmp1 && tmp1->redir)
	{
		tmp1->redir = handle_redir(init, tmp1->redir);
		if (!tmp1->redir)
		{
			tmp1->redir = tmp;
			return (0);
		}
		tmp1->redir = tmp1->redir->next;
	}
	cmd->redir = tmp;
	tmp1->redir = tmp;
	return (1);
}
