/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:50:47 by hlely             #+#    #+#             */
/*   Updated: 2018/03/07 16:19:34 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_redir	*handle_redir(t_redir *redir)
{
	if (ft_strequ(redir->token, ">"))
		redir = handle_simple(redir);
	else if (ft_strequ(redir->token, ">&"))
		redir = handle_simplefd(redir);
	else if (ft_strequ(redir->token, "<&"))
		redir = handle_backfd(redir);
	else if (ft_strequ(redir->token, ">>"))
		redir = handle_double(redir);
	else if (ft_strequ(redir->token, "<"))
		redir = handle_back(redir);
	else if (ft_strequ(redir->token, "<<"))
		redir = handle_heredoc(redir);
	else if (ft_strequ(redir->token, "&>"))
		redir = handle_redirall(redir);
	return (redir);
}

int		redirection(t_cmd *cmd)
{
	t_cmd	*tmp1;
	t_redir	*tmp;

	tmp1 = cmd;
	tmp = tmp1->redir;
	while (tmp1 && tmp1->redir)
	{
		tmp1->redir = handle_redir(tmp1->redir);
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
